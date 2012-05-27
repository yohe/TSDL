
#include "tsdl/scenario/scenario_entry.h"
#include "tsdl/scenario/scenario_case.h"
#include "tsdl/scenario/scenario_result_collector.h"


ScenarioCase::ScenarioCase(const std::string& scenario_file, const std::string& name, ScenarioEntry* parent) : ScenarioEntry(name, parent), scenario_(scenario_file) {

}

ScenarioCase::~ScenarioCase() {

}

ScenarioEntry::EntryType ScenarioCase::type() const {

    return ScenarioEntry::CASE;
}

bool ScenarioCase::execute(ScenarioResultCollector* collector) {

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

    if(parent_ == NULL) {
        return;
    }

    getParentPath(path);
}
