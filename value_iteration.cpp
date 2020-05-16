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
                               const std::unordered_map<std::string, int> &rf, const float &d, const std::string &t) : states(s), actions(a), reward_function(rf), discount(d), terminal(t)  {}

std::vector<int> stateMapping(std::string &s) //Helper Function - s -> (x,y)
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

int coordinateMapping(std::vector<int> c) //Helper Function - (x,y) -> s_i (index)
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
        std::vector<int> s_prime = stateMapping(state);
        //std::cout << state << " - " << s_prime[0] << " " << s_prime[1] << " ";

        bool action = false;
        for (std::string &a : actions)
        {
            if (a == "l" && (coordinates[0] - 1) == s_prime[0] && (coordinates[1]) == s_prime[1])
            {
                action = true;
                break;
            }
            if (a == "r" && (coordinates[0] + 1) == s_prime[0] && (coordinates[1]) == s_prime[1])
            {
                action = true;
                break;
            }
            if (a == "u" && (coordinates[1] + 1) == s_prime[1] && (coordinates[0]) == s_prime[0])
            {
                action = true;
                break;
            }
            if (a == "d" && (coordinates[1] - 1) == s_prime[1] && (coordinates[0]) == s_prime[0])
            {
                action = true;
                break;
            }
        }
        //std::cout << action << std::endl;
        return action;
    }
    std::vector<std::string> actions;
    std::vector<int> coordinates;
};

void ValueIteration::compute()
{
    std::vector<float> value_function(states.size());
    optimal_values.push_back(value_function);

    int k = 0;
    do
    {
        k++;
        //std::cout << k << std::endl;
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

            if (states[s] != "s3")
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

                float max_value = *std::max_element(std::begin(bellman_optimality), std::end(bellman_optimality));
                optimal_values[k][s] = max_value;
            }
            else
            {
                optimal_values[k][s] = 0;
            }
        }
        for (int i = 0; i < int(states.size()); ++i)
        {
            std::cout << optimal_values[k][i] << " ";
        }
        std::cout << std::endl
                  << std::endl;
    } while (!convergence());
}

bool ValueIteration::convergence(void)
{
    int k = optimal_values.size() - 1;
    for (int s = 0; s < int(states.size()); ++s)
    {
        if (optimal_values[k][s] - optimal_values[k - 1][s] > 0.1)
        {
            return false;
        }
    }
    return true;
}

void ValueIteration::write(std::ostream &os)
{
}

std::ostream &PLLKIA010::operator<<(std::ostream &os, const ValueIteration &v)
{
    return os;
}