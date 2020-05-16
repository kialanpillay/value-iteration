#include "value_iteration.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace PLLKIA010;

ValueIteration::ValueIteration(void){};

ValueIteration::ValueIteration(const std::vector<std::string> &s, const std::vector<std::string> &a,
                               const std::unordered_map<std::string, int> &rf, const float &d) : states(s), actions(a), reward_function(rf), discount(d) {}

std::ostream &PLLKIA010::operator<<(std::ostream &os, const ValueIteration &v)
{
    return os;
}