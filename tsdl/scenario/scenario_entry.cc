
#include "tsdl/scenario/scenario_entry.h"


ScenarioEntry::ScenarioEntry(const std::string& name, ScenarioEntry* parent) : name_(name), parent_(parent) {

}

ScenarioEntry::~ScenarioEntry() {

}

const std::string& ScenarioEntry::name() const {
    return name_;
}

ScenarioEntry* ScenarioEntry::parent() const {
    return parent_;
}

std::string ScenarioEntry::fullpath() const {
    std::string path("");
    getPath(path);
    return path;
}


void ScenarioEntry::getParentPath(std::string& path) const {
    parent_->getPath(path);
}

