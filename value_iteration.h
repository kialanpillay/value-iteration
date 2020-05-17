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
        ValueIteration(const std::vector<std::string> &states, const std::vector<std::string> &actions,
                       const std::unordered_map<std::string, int> &reward_function, const float &discount, const std::string &terminal);
        void runAlgorithm(void);
        void computePolicy(const std::string &start);
        void writeResults(std::ostream &os, const std::string &start);
        bool testConvergence(void) const;
        int getStateIndex(const std::string &s, const std::string &action) const;
        std::string getAction(const std::string &s, const std::string &s_prime) const;

    private:
        std::vector<std::string> states;
        std::vector<std::string> actions;
        std::unordered_map<std::string, int> reward_function;
        std::vector<std::vector<float>> optimal_values;
        std::vector<std::string> optimal_policy;
        float discount;
        std::string terminal;
    };
    std::ostream &operator<<(std::ostream &os, const ValueIteration &v);
} // namespace PLLKIA010

#endif