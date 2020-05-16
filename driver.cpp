#include "value_iteration.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;
using namespace PLLKIA010;

int main(int argc, char *argv[])
{
    vector<string> states = {"s1", "s2", "s3", "s4", "s5", "s6"};
    vector<string> actions = {"l", "r", "u", "d"};
    unordered_map<string, int> reward_function = {{"s2s3",50},{"s6s3",100}};
    float discount = 0.8;
    string terminal = "s3";

    ValueIteration module(states, actions, reward_function, discount, terminal);
    cout << module;
    return 0;
}
