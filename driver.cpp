#include "value_iteration.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;
using namespace PLLKIA010;

int main(int argc, char *argv[])
{
    ofstream out("output.txt");
    vector<string> states = {"s1", "s2", "s3", "s4", "s5", "s6"};
    vector<string> actions = {"left", "right", "up", "down"};
    unordered_map<string, int> reward_function = {{"s2s3",50},{"s6s3",100}};
    float discount = 0.8;
    string start = "s1";
    string terminal = "s3";

    ValueIteration module(states, actions, reward_function, discount, start, terminal);
    cout << module;
    out.close();
    return 0;
}
