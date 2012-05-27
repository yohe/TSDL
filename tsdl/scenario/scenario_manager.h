
#ifndef TSDL_SCENARIO_MANAGER_H
#define TSDL_SCENARIO_MANAGER_H

#include <string>
#include "tsdl/scenario/scenario_entry.h"

class ScenarioGroup;
class FormatOutputter;
class ScenarioResultCollector;

class ExecutorFactory;
class ConditionCheckerFactory;

class ScenarioTree {
public:
    ScenarioTree();
    ~ScenarioTree();

    ScenarioEntry* find(const std::string path) const;
    bool insert(const std::string& path, ScenarioEntry* entry, std::string& error);
    bool erase(const std::string& path, bool force, std::string& error);

    ScenarioEntry* root() const;
private:
    ScenarioGroup* root_;
};

class ScenarioManager {
public:
    ScenarioManager(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory,FormatOutputter* output, const std::string& config = "");

    bool setup();
    std::string getError();

    void executeAll(ScenarioResultCollector* collector);
    const ScenarioTree& getScenarioTree() const;

    const ScenarioEntry* getRootEntry() const;
    bool addScenario(const std::string& path, const std::string& scenarioFile);
    bool addGroup(const std::string& path);
    bool delScenario(const std::string& path);
    bool delGroup(const std::string& path, bool force = false);
    bool moveScenario(const std::string& oldPath, const std::string& newPath);
    bool moveGroup(const std::string& oldPath, const std::string& newPath);

    void writeConfig(const std::string& config);

private:
    bool addEntry(const std::string&path, ScenarioEntry::EntryType type, const std::string& scenarioFile = "");
    bool delEntry(const std::string&path, bool force);
    bool moveEntry(const std::string& oldPath, const std::string& newPath);

    std::string error_;
    ScenarioTree tree_;
    ExecutorFactory* exeFactory_;
    ConditionCheckerFactory* condFactory_;
    FormatOutputter* outputter_;
};
#endif /* end of include guard */

