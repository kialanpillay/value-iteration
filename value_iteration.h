#ifndef VALUE_ITERATION_H
#define VALUE_ITERATION_H
#include <unordered_map>
#include <vector>
#include <string>
 
namespace PLLKIA010
{
    class ValueIteration
    {   
        public: 
            ValueIteration(void);
            ValueIteration(const std::vector<std::string>& states, const std::vector<std::string>& actions, 
                            const std::unordered_map<std::string,int>& reward_function);
            void compute(std::ostream& os);
        private: 
            std::vector<std::string> states;
            std::vector<std::string> actions;
            std::unordered_map<std::string,int> reward_function;
            std::vector<std::vector<float>> optimal_values;
            std::vector<std::string> optimal_policy;
            float discount;
    };
    std::ostream& operator<<(std::ostream& os, const ValueIteration& v);  
}

#endif