
#ifndef TSDL_SCENARIO_SCENARIO_RESULT_COLLECTOR_H
#define TSDL_SCENARIO_SCENARIO_RESULT_COLLECTOR_H

#include <string>
#include <map>

class FormatOutputter;
class ScenarioEntry;
class ScenarioGroup;
class ScenarioResult;

class ScenarioResultCollector {
public:

    ScenarioResultCollector(ScenarioGroup* root);
    virtual ~ScenarioResultCollector();

    void addResult(const std::string& path, ScenarioResult* result);

    void output(FormatOutputter* outputter);

protected:

    void output(const std::string& path, ScenarioEntry* entry, FormatOutputter* outputter);

    ScenarioEntry* root_;
    std::map<std::string, ScenarioResult*> results_;
};

#endif /* end of include guard */

