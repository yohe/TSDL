
#ifndef TSDL_SCENARIO_SCENARIO_CASE_H
#define TSDL_SCENARIO_SCENARIO_CASE_H

#include <string>
#include "tsdl/lang/program_node.h"
#include "tsdl/scenario/scenario_entry.h"

class ExecutorFactory;
class ConditionCheckerFactory;
class ScenarioResultCollector;

class ScenarioCase : public ScenarioEntry {
public:
    ScenarioCase(const std::string& scenario_file, const std::string& name, ScenarioEntry* parent = NULL);

    virtual ~ScenarioCase();

    virtual EntryType type() const;

    virtual bool execute(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, ScenarioResultCollector* collector,
                         size_t& totalTests, size_t& totalFailures, size_t& totalErrors);

    virtual ScenarioEntry* find(const std::string& name) const;

    virtual size_t size() const;

protected:
    virtual ProgramNode* createProgramNode() const = 0;
    virtual void getPath(std::string& path) const;

    std::string scenario_;
};

#endif /* end of include guard */
