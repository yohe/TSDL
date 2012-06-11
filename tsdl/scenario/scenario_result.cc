
#include "tsdl/scenario/scenario_result.h"
#include <boost/date_time/time_duration.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>

ScenarioResult::ScenarioResult(const std::string& fullpath,
                               const std::string& name,
                               bool success,
                               const std::string& errorStr)
    : fullpath_(fullpath), name_(name), success_(success), errorStr_(errorStr), elapsedTime_("")
{

}
ScenarioResult::~ScenarioResult() {

}

void ScenarioResult::setTotal(size_t totalTests, size_t totalFailures, size_t totalErrors) {
    tests_ = totalTests;
    failures_= totalFailures;
    errors_= totalErrors;
}

void ScenarioResult::setTime(const boost::posix_time::time_duration& td) {
    std::cout << td.total_nanoseconds() << std::endl;
    elapsedTime_ = boost::posix_time::to_simple_string(td);
}
