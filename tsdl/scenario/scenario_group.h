
#ifndef TSDL_SCENARIO_SCENARIO_GROUP_H
#define TSDL_SCENARIO_SCENARIO_GROUP_H

#include <string>
#include <map>
#include "tsdl/scenario/scenario_entry.h"

class ExecutorFactory;
class ConditionCheckerFactory;
class ScenarioResultCollector;

class ScenarioGroup : public ScenarioEntry {
public:
    typedef std::map<std::string, ScenarioEntry*>::iterator iterator;
    typedef std::map<std::string, ScenarioEntry*>::const_iterator const_iterator;

    ScenarioGroup(const std::string& name, ScenarioEntry* parent = NULL);
    virtual ~ScenarioGroup();

    virtual EntryType type() const;

    virtual bool execute(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, ScenarioResultCollector* collector,
                         size_t& totalTests, size_t& totalFailures, size_t& totalErrors, time_duration& totalTimes);

    virtual ScenarioEntry* find(const std::string& name) const;

    virtual bool add(ScenarioEntry* entry);
    virtual bool remove(ScenarioEntry* entry);

    virtual size_t size() const;
    virtual size_t size_recursive() const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

protected:
    virtual void getPath(std::string& path) const;

    std::map<std::string, ScenarioEntry*> group_; 
};

#endif /* end of include guard */

