
#ifndef TSDL_LANG_CONDITION_CHECKER_H
#define TSDL_LANG_CONDITION_CHECKER_H

#include <string>

class ConditionChecker {
public:
    ConditionChecker() {}
    virtual ~ConditionChecker() {}
    virtual bool check(Result* result, std::string inputParam) = 0;
    virtual std::string getError() const = 0;
};

class ConditionCheckerFactory {
public:
    ConditionCheckerFactory() {}
    virtual ~ConditionCheckerFactory() {}
    virtual ConditionChecker* create(std::string name) = 0;
};

#endif /* end of include guard */
