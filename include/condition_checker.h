
#ifndef CONDITION_CHECKER_H_
#define CONDITION_CHECKER_H_

#include <string>

class ConditionChecker {
public:
    virtual bool check(Result* result, std::string inputParam) = 0;
    virtual std::string getError() const = 0;
};

class ConditionCheckerFactory {
public:
    virtual ConditionChecker* create(std::string name) = 0;
};

#endif /* end of include guard */
