#include "value_iteration.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>

using namespace PLLKIA010;

ValueIteration::ValueIteration(void){};

ValueIteration::ValueIteration(const std::vector<std::string> &s, const std::vector<std::string> &a,
                               const std::unordered_map<std::string, int> &rf, const float &d, const std::string &st, const std::string &t) : states(s), actions(a), reward_function(rf), discount(d), start(st), terminal(t) {}

std::vector<int> mapState(const std::string &s) //Helper Function - s -> (x,y)
{
    if (s == "s1")
    {
        return {0, 1};
    }
    if (s == "s2")
    {
        return {1, 1};
    }
    if (s == "s3")
    {
        return {2, 1};
    }
    if (s == "s4")
    {
        return {0, 0};
    }
    if (s == "s5")
    {
        return {1, 0};
    }
    if (s == "s6")
    {
        return {2, 0};
    }
    return {0, 0};
}

int mapCoordinates(const std::vector<int> c) //Helper Function - (x,y) -> s_i (index)
{
    if (c[0] == 0 && c[1] == 1)
    {
        return 0;
    }
    if (c[0] == 1 && c[1] == 1)
    {
        return 1;
    }
    if (c[0] == 2 && c[1] == 1)
    {
        return 2;
    }
    if (c[0] == 0 && c[1] == 0)
    {
        return 3;
    }
    if (c[0] == 1 && c[1] == 0)
    {
        return 4;
    }
    if (c[0] == 2 && c[1] == 0)
    {
        return 5;
    }
    return 0;
}

class Transition //Functor to determine if s -> s' is a valid transition
{
public:
    Transition(std::vector<std::string> &a, std::vector<int> c) : actions(a), coordinates(c) {}

    bool operator()(std::string &state)
    {
        std::vector<int> c_prime = mapState(state); //Coordinates of s'

        bool action = false;
        for (std::string &a : actions)
        {
            if (a == "left" && (coordinates[0] - 1) == c_prime[0] && (coordinates[1]) == c_prime[1])
            {
                action = true;
                break;
            }
            if (a == "right" && (coordinates[0] + 1) == c_prime[0] && (coordinates[1]) == c_prime[1])
            {
                action = true;
                break;
            }
            if (a == "up" && (coordinates[1] + 1) == c_prime[1] && (coordinates[0]) == c_prime[0])
            {
                action = true;
                break;
            }
            if (a == "down" && (coordinates[1] - 1) == c_prime[1] && (coordinates[0]) == c_prime[0])
            {
                action = true;
                break;
            }
        }
        return action;
    }
    std::vector<std::string> actions;
    std::vector<int> coordinates;
};

void ValueIteration::runAlgorithm()
{
    optimal_values.clear();
    std::vector<float> value_function(states.size());
    optimal_values.push_back(value_function);

    int k = 0;
    do
    {
        k++;
        optimal_values.push_back(value_function);
        for (int s = 0; s < int(states.size()); ++s)
        {
            std::vector<float> discounted_value(states.size()); //V(s') for all states
            std::vector<std::string> transition;                //Possible transitions from s -> s'
            std::vector<int> reward;                            //Immediate reward for s -> s'
            std::vector<float> transition_state_value;          //V(s') for all possible transitions
            std::transform(optimal_values[k - 1].begin(), optimal_values[k - 1].end(), discounted_value.begin(), [this](float f) { return discount * f; });

            std::unordered_map<std::string, float> state_value; //Map from s to V(s)
            for (int r = 0; r < int(discounted_value.size()); ++r)
            {
                state_value.insert({states[r], discounted_value[r]});
            }

            if (states[s] != terminal)
            {

                std::copy_if(states.begin(), states.end(), std::back_inserter(transition), Transition(actions, mapState(states[s])));

                for (std::string &t : transition)
                {
                    transition_state_value.push_back(state_value[t]);

                    auto it = reward_function.find(states[s] + t);
                    if (it != reward_function.end())
                    {
                        reward.push_back(it->second);
                    }
                    else
                    {
                        reward.push_back(0);
                    }
                }
                std::vector<float> bellman_optimality(transition.size()); //R + V(s') for all transitions
                for (int i = 0; i < int(bellman_optimality.size()); ++i)
                {
                    bellman_optimality[i] = reward[i] + transition_state_value[i];
                }

                float max_value = *std::max_element(bellman_optimality.begin(), bellman_optimality.end()); //Maximal value
                optimal_values[k][s] = max_value;
            }
            else
            {
                optimal_values[k][s] = 0;
            }
        }
    } while (!testConvergence());
    iterations = k;
}

int ValueIteration::getStateIndex(const std::string &s, const std::string &action) const
{
    std::vector<int> c = mapState(s);
    if (action == actions[0])
    {
        c[0] -= 1;
        return mapCoordinates(c);
    }
    if (action == actions[1])
    {
        c[0] += 1;
        return mapCoordinates(c);
    }
    if (action == actions[2])
    {
        c[1] += 1;
        return mapCoordinates(c);
    }
    else
    {
        c[1] -= 1;
        return mapCoordinates(c);
    }
}

std::string ValueIteration::getAction(const std::string &s, const std::string &s_prime) const
{
    std::vector<int> c = mapState(s);
    std::vector<int> c_prime = mapState(s_prime);
    if ((c[0] - 1) == c_prime[0] && (c[1]) == c_prime[1])
    {
        return actions[0];
    }
    if ((c[0] + 1) == c_prime[0] && (c[1]) == c_prime[1])
    {
        return actions[1];
    }
    if ((c[1] + 1) == c_prime[1] && (c[0]) == c_prime[0])
    {
        return actions[2];
    }
    else
    {
        return actions[3];
    }
}

bool ValueIteration::testConvergence(void) const
{
    int k = optimal_values.size() - 1;
    for (int s = 0; s < int(states.size()); ++s)
    {
        if (optimal_values[k][s] - optimal_values[k - 1][s] > 0.00001)
        {
            return false;
        }
    }
    return true;
}

void ValueIteration::computePolicy()
{
    optimal_policy.clear();
    std::string state = start;
    std::unordered_map<std::string, float> state_optimal_value;
    for (int o = 0; o < int(states.size()); ++o)
    {
        state_optimal_value.insert({states[o], discount * optimal_values[optimal_values.size() - 1][o]});
    }
    for (int s = 0; s < int(states.size()); ++s)
    {
        std::vector<std::string> transition;
        std::vector<int> reward;
        std::vector<float> transition_state_value;

        if (states[s] != terminal)
        {

            std::copy_if(states.begin(), states.end(), std::back_inserter(transition), Transition(actions, mapState(states[s])));

            for (std::string &t : transition)
            {
                transition_state_value.push_back(state_optimal_value[t]);

                auto it = reward_function.find(states[s] + t);
                if (it != reward_function.end())
                {
                    reward.push_back(it->second);
                }
                else
                {
                    reward.push_back(0);
                }
            }
            std::vector<float> bellman_optimality(transition.size());

            for (int i = 0; i < int(bellman_optimality.size()); ++i)
            {
                bellman_optimality[i] = reward[i] + transition_state_value[i];
            }
            auto it = std::find(bellman_optimality.begin(), bellman_optimality.end(), *std::max_element(bellman_optimality.begin(), bellman_optimality.end()));
            int index = std::distance(bellman_optimality.begin(), it);
            std::string action = getAction(states[s], transition[index]);
            optimal_policy.insert({states[s], action});
        }
        else
        {
            optimal_policy.insert({states[s], "none"});
        }
    }
}

void ValueIteration::writeResults(std::ostream &os)
{
    os << "Question 1" << std::endl;
    os << "----------" << std::endl;
    os << "Iterations:  " << iterations << std::endl
       << std::endl;

    os << "Optimal Values:  \n";
    for (int i = 0; i < int(states.size()); ++i)
    {
        os << states[i] << " - " << optimal_values[optimal_values.size() - 1][i] << "\n";
    }
    os << std::endl;

    os << "Question 2" << std::endl;
    os << "----------" << std::endl;
    os << "Optimal Policy (Actions): ";
    std::string state = start;
    while (state != terminal)
    {
        os << optimal_policy[state] << " ";
        state = states[getStateIndex(state, optimal_policy[state])];
    }
    std::unordered_map<std::string, std::string> cache = optimal_policy;
    os << std::endl;

    state = start;
    os << "Optimal Policy (States): ";
    os << state << " ";

    while (state != terminal)
    {
        state = states[getStateIndex(state, optimal_policy[state])];
        os << state << " ";
    }
    os << std::endl
       << std::endl;

    os << "Question 3" << std::endl;
    os << "----------" << std::endl;

    reward_function = {{"s2s3", 100}, {"s6s3", 200}};
    runAlgorithm();
    computePolicy();

    bool policy_change = false;
    for (int i = 0; i < int(states.size()); ++i)
    {
        if (cache[states[i]] != optimal_policy[states[i]])
        {
            policy_change = true;
            break;
        }
    }

    if (!policy_change)
    {

        os << "Reward Function Change: (1,1) -> (1,2); R = 100  \n";
        os << "Reward Function Change: (2,0) -> (2,1); R = 200  \n";
        os << "Updated Optimal Values:  \n";
        for (int i = 0; i < int(states.size()); ++i)
        {
            os << states[i] << " - " << optimal_values[optimal_values.size() - 1][i] << "\n";
        }
        os << std::endl;
        os << "No Optimal Policy Change" << std::endl
           << std::endl;
        os << "Optimal Policy (Actions): ";
        state = start;

        while (state != terminal)
        {
            os << optimal_policy[state] << " ";
            state = states[getStateIndex(state, optimal_policy[state])];
        }
        os << std::endl;

        state = start;
        os << "Optimal Policy (States): ";
        os << state << " ";

        while (state != terminal)
        {
            state = states[getStateIndex(state, optimal_policy[state])];
            os << state << " ";
        }
    }
    else
    {
        os << "Optimal Policy Change Guaranteed";
    }
}

std::ostream &PLLKIA010::operator<<(std::ostream &os, const ValueIteration &v)
{
    os << "ML Assignment 6: Value Iteration" << std::endl
       << "================================" << std::endl;
    os << "Kialan Pillay: PLLKIA010" << std::endl
       << "================================" << std::endl
       << std::endl;
    ValueIteration value_iteration = v;
    value_iteration.runAlgorithm();
    value_iteration.computePolicy();
    value_iteration.writeResults(os);
    return os;
}