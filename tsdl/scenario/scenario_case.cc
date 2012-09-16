
#include <fstream>

#include "tsdl/scenario/scenario_case.h"
#include "tsdl/scenario/scenario_result.h"
#include "tsdl/scenario/scenario_result_collector.h"
#include "tsdl/scenario/scenario_timer.h"

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

bool ScenarioCase::execute(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, ScenarioResultCollector* collector,
                           size_t& totalTests, size_t& totalFailures, size_t& totalErrors, time_duration& totalTimes) {
    totalTests++;

    std::string path = fullpath();

    std::ifstream* ifs = NULL;
    ifs = new  std::ifstream(scenario_.c_str());
    if(!ifs->is_open()) {
        std::string errorStr = "ScenarioFile open error. [" + scenario_ + "]";
        ScenarioResult* result = new ScenarioResult(path, name_, false, errorStr);
        collector->addResult(path, result);
        delete ifs;
        totalErrors++;
        return false;
    }

    CountUpTimer cut;
    Context c(ifs);

    ProgramNode* p = createProgramNode();
    try {
        cut.set();
        p->parse(c);
        p->setExecutorFactory(exeFactory);
        p->setConditionCheckerFactory(condFactory);
        p->execute();
    } catch (ParseException& e) {
        ScenarioResult* result = new ScenarioResult(path, name_, false, e.what());
        collector->addResult(path, result);
        totalErrors++;
        return false;
    } catch (ExecuteException& e) {
        ScenarioResult* result = new ScenarioResult(path, name_, false, e.what());
        collector->addResult(path, result);
        totalFailures++;
        return false;
    }
    delete ifs;
    delete p;

    time_duration td = cut.elapsed();
    totalTimes += td;

    ScenarioResult* result = new ScenarioResult(path, name_, true);
    Timer timer;
    result->setTime(timer.now());
    result->setElapsedTime(td);
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
