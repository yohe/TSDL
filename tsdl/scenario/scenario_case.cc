
#include <fstream>

#include "tsdl/scenario/scenario_entry.h"
#include "tsdl/scenario/scenario_case.h"
#include "tsdl/scenario/scenario_result.h"
#include "tsdl/scenario/scenario_result_collector.h"

#include "tsdl/lang/context.h"
#include "tsdl/lang/program_node.h"
#include "tsdl/lang/executor.h"
#include "tsdl/lang/condition_checker.h"

ScenarioCase::ScenarioCase(const std::string& scenario_file, const std::string& name, ScenarioEntry* parent) : ScenarioEntry(name, parent), scenario_(scenario_file) {

}

ScenarioCase::~ScenarioCase() {

}

ScenarioEntry::EntryType ScenarioCase::type() const {

    return ScenarioEntry::CASE;
}

bool ScenarioCase::execute(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, ScenarioResultCollector* collector) {
    std::string path = fullpath();

    std::ifstream* ifs = NULL;
    ifs = new  std::ifstream(scenario_.c_str());
    if(!ifs->is_open()) {
        std::string errorStr = "ScenarioFile open error. [" + scenario_ + "]";
        ScenarioResult* result = new ScenarioResult(path, name_, false, errorStr);
        collector->addResult(path, result);
        return false;
    }

    Context c(ifs);

    ProgramNode p;
    try {
        p.parse(c);
        p.setExecutorFactory(exeFactory);
        p.setConditionCheckerFactory(condFactory);
        p.execute();
    } catch (ParseException& e) {
        ScenarioResult* result = new ScenarioResult(path, name_, false, e.what());
        collector->addResult(path, result);
        return false;
    } catch (ExecuteException& e) {
        ScenarioResult* result = new ScenarioResult(path, name_, false, e.what());
        collector->addResult(path, result);
        return false;
    }
    delete ifs;

    ScenarioResult* result = new ScenarioResult(path, name_, true);
    collector->addResult(path, result);

    return true;
}

ScenarioEntry* ScenarioCase::find(const std::string& name) const {
    return NULL;
}

size_t ScenarioCase::size() const {
    return 1;
}

void ScenarioCase::getPath(std::string& path) const {
    path.insert(0, name_);
    getParentPath(path);
}
