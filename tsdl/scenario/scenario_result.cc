
#include "tsdl/scenario/scenario_result.h"

ScenarioResult::ScenarioResult(const std::string& fullpath,
                               const std::string& name,
                               bool success,
                               const std::string& errorStr)
    : fullpath_(fullpath), name_(name), success_(success), errorStr_(errorStr)
{

}
ScenarioResult::~ScenarioResult() {

}

