
#include "tsdl/scenario/scenario_result.h"
#include <boost/date_time/time_duration.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>

#include <iomanip>
#include <sstream>

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

void ScenarioResult::setTime(const boost::posix_time::ptime& pt) {
    pt_ = pt;
}

void ScenarioResult::setElapsedTime(const boost::posix_time::time_duration& td) {
    std::stringstream ss;
    if(td.resolution() == boost::date_time::nano) {
        ss << td.total_seconds() << std::setw(9) << std::setfill('0') << td.fractional_seconds();
    } else if(td.resolution() == boost::date_time::micro) {
        ss << td.total_seconds() << "." << std::setw(6) << std::setfill('0') << td.fractional_seconds();
    }
    //elapsedTime_ = boost::posix_time::to_simple_string(td);
    elapsedTime_ = ss.str();
}
