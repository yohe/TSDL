
#include "tsdl/scenario/scenario_result_collector.h"
#include "tsdl/scenario/scenario_entry.h"
#include "tsdl/scenario/scenario_group.h"
#include "tsdl/outputter/format_outputter.h"

ScenarioResultCollector::ScenarioResultCollector(ScenarioGroup* root) : root_(root) {

}

ScenarioResultCollector::~ScenarioResultCollector() {

}

void ScenarioResultCollector::addResult(const std::string& path, ScenarioResult* result) {
    if(results_.count(path) != 0) {
        return;
    }
    if(path.size() == 1) {
        results_[path] = result;
        return;
    }
    std::cout << "Add+++++ [" << path << "]" << std::endl;

    results_[path] = result;
}

void ScenarioResultCollector::output(FormatOutputter* outputter) {

    outputter->start();
    output("", root_, outputter);
    outputter->end();
}

void ScenarioResultCollector::output(const std::string& parentPath, ScenarioEntry* entry, FormatOutputter* outputter) {
    //std::cout << parentPath <<std::endl;
    //std::cout << entry->name() <<std::endl;

    std::string path = parentPath + entry->name();
    if(entry->type() == ScenarioEntry::GROUP) {
        path.append("/");
    }
    std::cout << "PointB  " << path << std::endl;
    if(results_.count(path) == 0) {
        std::cout << "PointC----- [" << path << "]" << std::endl;
        return;
    }
    ScenarioResult* result = results_.at(path);


    if(entry->type() == ScenarioEntry::CASE) {
        outputter->write(result);
        return;
    } else {

    }

    ScenarioGroup* group = dynamic_cast<ScenarioGroup*>(entry);
    outputter->start(result);
    for(ScenarioGroup::iterator ite = group->begin(); ite != group->end(); ++ite) {
        output(path, ite->second, outputter);
    }
    outputter->end(result);
}


void ScenarioResultCollector::setRoot(ScenarioGroup* root) {
    root_ = root;
}
