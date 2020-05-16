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
                               const std::unordered_map<std::string, int> &rf, const float &d) : states(s), actions(a), reward_function(rf), discount(d) {}


std::vector<int> stateMapping(std::string &s)
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
    return {0,0};
}

int coordinateMapping(std::vector<int> c)
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
        std::cout << state  << " - " << s_prime[0] << " " << s_prime[1] << " ";

        bool action = false;
        for (std::string &a : actions)
        {
            if (a == "l" && (coordinates[0] - 1) == s_prime[0] && (coordinates[1]) == s_prime[1])
            {
                action =  true;
                break;
            }
            if (a == "r" && (coordinates[0] + 1) == s_prime[0] && (coordinates[1]) == s_prime[1])
            {
                action =  true;
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
        std::cout << action << std::endl;
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
    while (k < 1)
    {
        k++;
        optimal_values.push_back(value_function);
        for (int s = 0; s < 1; ++s)
        {
            std::vector<float> discounted_reward(states.size()); //V(s') for all states
            std::vector<std::string> transition; 
            std::vector<float> transition_state_reward;          //V(s') for all possible transitions
            std::transform(optimal_values[k - 1].begin(), optimal_values[k - 1].end(), discounted_reward.begin(), [this](float f) { return discount * f; });
            std::copy_if(states.begin(), states.end(), std::back_inserter(transition), Transition(actions, stateMapping(states[s])));
            //float max_reward = discount * *std::max_element(std::begin(optimal_values[k-1]), std::end(optimal_values[k-1]));
            int reward = 0;
            optimal_values[k][s] = reward;
        }
    }
}

bool ValueIteration::convergence(void)
{
    int k = optimal_values.size();
    for (int s = 0; s < int(states.size()); ++s)
    {
        if (optimal_values[k][s] - optimal_values[k][s] > 0.0001)
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