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

void ValueIteration::compute(){
    std::vector<float> value_function(states.size());
    optimal_values.push_back(value_function);

    for(std::string& s: states){

    }
}

bool ValueIteration::convergence(void){
    int k = optimal_values.size();
    for(int s = 0; s < int(states.size()); ++s){
        if(optimal_values[k][s]-optimal_values[k][s] > 0.0001){
            return false;
        }
    }
    return true;
}

void ValueIteration::write(std::ostream &os){

}

std::ostream &PLLKIA010::operator<<(std::ostream &os, const ValueIteration &v)
{
    return os;
}