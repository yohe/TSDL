
#ifndef TSDL_SCENARIO_SCENARIO_RESULT_COLLECTOR_H
#define TSDL_SCENARIO_SCENARIO_RESULT_COLLECTOR_H

#include <string>
#include <map>

class FormatOutputter;
class ScenarioEntry;
class ScenarioGroup;
class ScenarioResult;

class ScenarioResultCollector {
    typedef std::map<std::string, ScenarioResult*> ResultMap;
public:

    ScenarioResultCollector(ScenarioGroup* root = NULL);
    virtual ~ScenarioResultCollector();

    void addResult(const std::string& path, ScenarioResult* result);

    void output(FormatOutputter* outputter);

    void setRoot(ScenarioGroup* root);

protected:

    void output(const std::string& path, ScenarioEntry* entry, FormatOutputter* outputter);

    ScenarioEntry* root_;
    ResultMap results_;
};

#endif /* end of include guard */

