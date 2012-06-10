
#ifndef TSDL_SCENARIO_SCENARIO_RESULT_H
#define TSDL_SCENARIO_SCENARIO_RESULT_H

#include <string>
#include <boost/date_time.hpp>

//namespace boost {
//    namespace posix_time {
//        class time_duration;
//    }
//};

using namespace boost::posix_time;
class Outputter;

class ScenarioResult {
public:
    ScenarioResult(const std::string& fullpath, const std::string& name, bool success, const std::string& errorStr = "");
    virtual ~ScenarioResult();

    void setTotal(size_t totalTests, size_t totalFailures, size_t totalErrors);
    void setTime(const time_duration& td);

    std::string fullpath_;
    std::string name_;
    bool success_;
    std::string errorStr_;
    std::string elapsedTime_;

    size_t tests_;
    size_t failures_;
    size_t errors_;
};

#endif /* end of include guard */

