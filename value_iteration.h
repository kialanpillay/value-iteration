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
                       const std::unordered_map<std::string, int> &reward_function, const float &discount, const std::string &start, const std::string &terminal);
        void runAlgorithm(void);
        void computePolicy(void);
        void writeResults(std::ostream &os);
        bool testConvergence(void) const;
        int getStateIndex(const std::string &s, const std::string &action) const;
        std::string getAction(const std::string &s, const std::string &s_prime) const;
        int getIterations() const;
        std::vector<float> getOptimalValues() const;
        std::unordered_map<std::string, std::string> getOptimalPolicy() const;

    private:
        std::vector<std::string> states;
        std::vector<std::string> actions;
        std::unordered_map<std::string, int> reward_function;
        std::vector<std::vector<float>> optimal_values;
        std::unordered_map<std::string, std::string> optimal_policy;
        float discount;
        std::string start;
        std::string terminal;
        int iterations;
    };
    std::ostream &operator<<(std::ostream &os, const ValueIteration &v);
} // namespace PLLKIA010

#endif