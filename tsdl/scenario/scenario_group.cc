
#include "tsdl/scenario/scenario_entry.h"
#include "tsdl/scenario/scenario_group.h"
#include "tsdl/scenario/scenario_result.h"
#include "tsdl/scenario/scenario_result_collector.h"

#include "tsdl/lang/context.h"
#include "tsdl/lang/program_node.h"
#include "tsdl/lang/executor.h"
#include "tsdl/lang/condition_checker.h"

ScenarioGroup::ScenarioGroup(const std::string& name, ScenarioEntry* parent) : ScenarioEntry(name, parent) {

}

ScenarioGroup::~ScenarioGroup() {

}

ScenarioEntry::EntryType ScenarioGroup::type() const {

    return ScenarioEntry::GROUP;
}

bool ScenarioGroup::execute(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, ScenarioResultCollector* collector) {
    bool success = true;
    for(iterator ite = begin(); ite != end(); ++ite) {
        success = (success & ite->second->execute(exeFactory, condFactory, collector));
    }
    std::string path = fullpath();
    ScenarioResult* result = new ScenarioResult(path, name_, success);
    collector->addResult(path, result);
    
    return success;
}

ScenarioEntry* ScenarioGroup::find(const std::string& name) const {

    if(group_.count(name) == 0) {
        return NULL;
    }

    return (group_.find(name)->second);
}

bool ScenarioGroup::add(ScenarioEntry* entry) {

    if (group_.count(entry->name()) == 1) {
        return false;
    }

    group_.insert(std::make_pair(entry->name(), entry));
    return true;
}

bool ScenarioGroup::remove(ScenarioEntry* entry) {

    if (group_.count(entry->name()) == 0) {
        return false;
    }

    group_.erase(entry->name());
    return true;
}

size_t ScenarioGroup::size() const {
    return group_.size();
}

size_t ScenarioGroup::size_recursive() const {

    size_t sum = 0;
    
    return sum;
}

ScenarioGroup::iterator ScenarioGroup::begin() {
    return group_.begin();
}
ScenarioGroup::iterator ScenarioGroup::end() {
    return group_.end();
}

ScenarioGroup::const_iterator ScenarioGroup::begin() const {
    return group_.begin();
}
ScenarioGroup::const_iterator ScenarioGroup::end() const {
    return group_.end();
}

void ScenarioGroup::getPath(std::string& path) const {
    if(parent_ == NULL) {
        path.insert(0, "/");
        return;
    } else {
        std::string str = name_ + "/";
        path.insert(0, str);
        getParentPath(path);
    }
}
