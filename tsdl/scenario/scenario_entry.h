
#ifndef TSDL_SCENARIO_SCENARIO_ENTRY_H
#define TSDL_SCENARIO_SCENARIO_ENTRY_H

#include <string>
#include <boost/date_time.hpp>
using namespace boost::posix_time;

class ExecutorFactory;
class ConditionCheckerFactory;

class ScenarioResultCollector;

class ScenarioEntry {
public:
    enum EntryType {
        CASE,
        GROUP
    };

    ScenarioEntry(const std::string& name, ScenarioEntry* parent);
    virtual ~ScenarioEntry();

    const std::string& name() const;
    virtual EntryType type() const = 0;
    virtual ScenarioEntry* find(const std::string& name) const = 0;

    virtual bool execute(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, ScenarioResultCollector* collector,
                         size_t& totalTests, size_t& totalFailures, size_t& totalErrors, time_duration& totalTime) = 0;

    virtual size_t size() const = 0;
    ScenarioEntry* parent() const;

    std::string fullpath() const;

protected:
    virtual void getPath(std::string& path) const = 0;
    void getParentPath(std::string& path) const;
    void setParent(ScenarioEntry* parent);

protected:
    std::string name_;
    ScenarioEntry* parent_;
};

#endif /* end of include guard */
