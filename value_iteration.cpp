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
                               const std::unordered_map<std::string, int> &rf, const float &d, const std::string &t) : states(s), actions(a), reward_function(rf), discount(d), terminal(t) {}

std::vector<int> stateMapping(const std::string &s) //Helper Function - s -> (x,y)
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

int coordinateMapping(const std::vector<int> c) //Helper Function - (x,y) -> s_i (index)
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
        std::vector<int> c_prime = stateMapping(state); //Coordinates of successor state

        bool action = false;
        for (std::string &a : actions)
        {
            if (a == "l" && (coordinates[0] - 1) == c_prime[0] && (coordinates[1]) == c_prime[1])
            {
                action = true;
                break;
            }
            if (a == "r" && (coordinates[0] + 1) == c_prime[0] && (coordinates[1]) == c_prime[1])
            {
                action = true;
                break;
            }
            if (a == "u" && (coordinates[1] + 1) == c_prime[1] && (coordinates[0]) == c_prime[0])
            {
                action = true;
                break;
            }
            if (a == "d" && (coordinates[1] - 1) == c_prime[1] && (coordinates[0]) == c_prime[0])
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
    std::vector<float> value_function(states.size());
    optimal_values.push_back(value_function);

    int k = 0;
    do
    {
        k++;
        optimal_policy.clear();
        bool terminated = false;
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
                state_value.insert({states[r], discounted_value[r]}); //Populate map
            }

            if (states[s] != "s3") //If not Terminal state
            {

                std::copy_if(states.begin(), states.end(), std::back_inserter(transition), Transition(actions, stateMapping(states[s])));

                for (std::string &t : transition)
                {
                    transition_state_value.push_back(state_value[t]);
                }

                for (std::string &t : transition)
                {
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
                /*
                if (!terminated)
                {
                    if (std::find(transition.begin(), transition.end(), "s3") != transition.end())
                    {
                        optimal_policy.push_back(getAction(states[s], "s3"));
                        terminated = true;
                    }
                    else
                    {
                        auto it = std::find(bellman_optimality.begin(), bellman_optimality.end(), max_value);
                        int index = std::distance(bellman_optimality.begin(), it);
                        optimal_policy.push_back(getAction(states[s], transition[index]));
                    }
                }*/
            }
            else
            {
                optimal_values[k][s] = 0;
            }
        }
    } while (!testConvergence());
}

int ValueIteration::getStateIndex(const std::string &s, const std::string &action) const
{
    std::vector<int> c = stateMapping(s);
    if (action == "left")
    {
        c[0] -= 1;
        return coordinateMapping(c);
    }
    if (action == "right")
    {
        c[0] += 1;
        return coordinateMapping(c);
    }
    if (action == "up")
    {
        c[1] += 1;
        return coordinateMapping(c);
    }
    else
    {
        c[1] -= 1;
        return coordinateMapping(c);
    }
}

std::string ValueIteration::getAction(const std::string &s, const std::string &s_prime) const
{
    std::vector<int> c = stateMapping(s);
    std::vector<int> c_prime = stateMapping(s_prime);
    if ((c[0] - 1) == c_prime[0] && (c[1]) == c_prime[1])
    {
        return "left";
    }
    if ((c[0] + 1) == c_prime[0] && (c[1]) == c_prime[1])
    {
        return "right";
    }
    if ((c[1] + 1) == c_prime[1] && (c[0]) == c_prime[0])
    {
        return "up";
    }
    else
    {
        return "down";
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

void ValueIteration::computePolicy(const std::string &start)
{
    std::string state = start;
    int p = 0;
    bool terminated = false;
    std::vector<std::string> transition;
    std::vector<float> values;

    std::unordered_map<std::string, float> state_optimal_value;
    for (int o = 0; o < int(optimal_values.size()); ++o)
    {
        state_optimal_value.insert({states[o], optimal_values[optimal_values.size() - 1][o]});
    }

    while (!terminated)
    {
        transition.clear();
        values.clear();
        std::copy_if(states.begin(), states.end(), std::back_inserter(transition), Transition(actions, stateMapping(state)));
        for (std::string &t : transition)
        {
            values.push_back(state_optimal_value[t]);
        }

        if (std::find(transition.begin(), transition.end(), "s3") != transition.end())
        {
            optimal_policy.push_back(getAction(state, "s3"));
            terminated = true;
        }
        else
        {
            auto it = std::find(values.begin(), values.end(), *std::max_element(values.begin(), values.end()));
            int index = std::distance(values.begin(), it);
            optimal_policy.push_back(getAction(state, transition[index]));
        }
        state = states[getStateIndex(state, optimal_policy[p])];
        p++;
    }
}

void ValueIteration::writeResults(std::ostream &os, const std::string &start)
{

    os << "Optimal Values:  \n";
    for (int i = 0; i < int(states.size()); ++i)
    {
        std::cout << states[i] << " - " << optimal_values[optimal_values.size() - 1][i] << "\n";
    }
    std::cout << std::endl;

    os << "Optimal Policy (Actions): ";
    for (int i = 0; i < int(optimal_policy.size()); ++i)
    {
        os << optimal_policy[i] << " ";
    }
    os << std::endl;

    std::string state = start;
    os << "Optimal Policy (States): ";
    os << state << " ";
    for (int i = 0; i < int(optimal_policy.size()); ++i)
    {
        state = states[getStateIndex(state, optimal_policy[i])];
        os << state << " ";
    }
}

std::ostream &PLLKIA010::operator<<(std::ostream &os, const ValueIteration &v)
{
    ValueIteration value_iteration = v;
    value_iteration.runAlgorithm();
    value_iteration.computePolicy("s1");
    value_iteration.writeResults(os, "s1");
    return os;
}