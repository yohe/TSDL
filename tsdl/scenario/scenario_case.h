
#ifndef TSDL_SCENARIO_SCENARIO_CASE_H
#define TSDL_SCENARIO_SCENARIO_CASE_H

#include <string>

class ExecutorFactory;
class ConditionCheckerFactory;
class ScenarioEntry;
class ScenarioResultCollector;

class ScenarioCase : public ScenarioEntry {
public:
    ScenarioCase(const std::string& scenario_file, const std::string& name, ScenarioEntry* parent = NULL);

    virtual ~ScenarioCase();

    virtual EntryType type() const;

    virtual bool execute(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, ScenarioResultCollector* collector);

    virtual ScenarioEntry* find(const std::string& name) const;

    virtual size_t size() const;

protected:
    virtual void getPath(std::string& path) const;

    std::string scenario_;
};

#endif /* end of include guard */
