
#ifndef TSDL_SCENARIO_SCENARIO_RESULT_H
#define TSDL_SCENARIO_SCENARIO_RESULT_H

#include <string>

class Outputter;

class ScenarioResult {
public:
    ScenarioResult(const std::string& fullpath, const std::string& name, bool success, const std::string& errorStr = "");
    virtual ~ScenarioResult();

    void setTotal(size_t totalTests, size_t totalFailures, size_t totalErrors);

    std::string fullpath_;
    std::string name_;
    bool success_;
    std::string errorStr_;

    size_t tests_;
    size_t failures_;
    size_t errors_;
};

#endif /* end of include guard */

