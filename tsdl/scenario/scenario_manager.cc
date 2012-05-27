
#include "tsdl/scenario/scenario_entry.h"
#include "tsdl/scenario/scenario_case.h"
#include "tsdl/scenario/scenario_group.h"
#include "tsdl/scenario/scenario_manager.h"
#include "tsdl/scenario/scenario_result_collector.h"

#include <boost/tokenizer.hpp>

ScenarioTree::ScenarioTree() {
    root_ = new ScenarioGroup("", NULL);
}

ScenarioTree::~ScenarioTree() {

    delete root_;
}

ScenarioEntry* ScenarioTree::root() const {
    return root_;
}

ScenarioEntry* ScenarioTree::find(const std::string path) const {

    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char> > tokens(path, sep);

    ScenarioEntry* entry = root_;
    typedef boost::tokenizer<boost::char_separator<char> >::iterator Iterator;
    for(Iterator ite = tokens.begin(); ite != tokens.end(); ite++) {
        ScenarioEntry* find = entry->find(*ite);

        if(find == NULL) {
            return NULL;
        }

        entry = find;
    }

    return entry;
}

bool ScenarioTree::insert(const std::string& path, ScenarioEntry* entry, std::string& error) {
    //std::cout << "[" << path << entry->name() << "]" << std::endl;;

    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char> > tokens(path, sep);

    ScenarioEntry* insertDir = root_;
    ScenarioEntry* insertEntry = entry;
    typedef boost::tokenizer<boost::char_separator<char> >::iterator Iterator;
    Iterator ite = tokens.begin();

    //std::cout << "--------------------------------" << std::endl;;
    for(; ite != tokens.end(); ite++) {
        ScenarioEntry* find = insertDir->find(*ite);
        //std::cout << "[" << *ite << "]" << std::endl;;
        //std::cout << find << std::endl;;

        if(find == NULL) {
            //std::cout << "find == NULL" << std::endl;
            break;
        }
        insertDir = find;
    }

    // incomplete path.
    if(ite != tokens.end()) {
        error = path + " isn't exist.";
        return false;
    }

    // this entry is not group.
    if(insertDir->type() != ScenarioEntry::GROUP) {
        error = insertDir->name() + " isn't group.";
        return false;
    }

    // already exist.
    if(insertDir->find(entry->name()) != NULL) {
        error = entry->name() + " is already exist.";
        return false;
    }

    ScenarioGroup* dir = dynamic_cast<ScenarioGroup*>(insertDir);
    dir->add(insertEntry);

    return true;
}

bool ScenarioTree::erase(const std::string& path, bool force, std::string& error) {
    //std::cout << "[" << path << "]" << std::endl;;

    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char> > tokens(path, sep);

    ScenarioEntry* searchDir = root_;

    ScenarioEntry* eraseDir = root_;
    ScenarioEntry* eraseEntry = NULL;

    typedef boost::tokenizer<boost::char_separator<char> >::iterator Iterator;
    Iterator ite = tokens.begin();

    //std::cout << "--------------------------------" << std::endl;;
    for(; ite != tokens.end(); ite++) {
        ScenarioEntry* find = searchDir->find(*ite);
        //std::cout << "[" << *ite << "]" << std::endl;;

        if(find == NULL) {
            //std::cout << "find == NULL" << std::endl;
            break;
        }

        eraseEntry = find;
        if(find->type() == ScenarioEntry::GROUP) {
            eraseDir = searchDir;
            searchDir = find;
        } else {
            ite++;
            break;
        }
    }
    //std::cout << "--------------------------------" << std::endl;;
    //std::cout << eraseDir << std::endl;;
    //std::cout << eraseEntry << std::endl;;

    // incomplete path.
    if(ite != tokens.end()) {
        error = path + " isn't exsit.";
        return false;
    }
    //std::cout << "--------------------------------" << std::endl;;

    // children exist.
    if(eraseEntry->type() == ScenarioEntry::GROUP && eraseEntry->size() != 0) {
        if( !force ) {
            error = eraseEntry->name() + " has children yet.";
            return false;
        }
    }
    
    //std::cout << eraseEntry->name() << std::endl;;
    ScenarioGroup* dir = dynamic_cast<ScenarioGroup*>(eraseDir);
    dir->remove(eraseEntry);
    delete eraseEntry;

    return true;
}


ScenarioManager::ScenarioManager(FormatOutputter* output, const std::string& config) {
}


bool ScenarioManager::setup() {

    return true;
}
std::string ScenarioManager::getError() {

    return error_;
}

void ScenarioManager::executeAll(ScenarioResultCollector* collector) {
    tree_.root()->execute(collector);
}
const ScenarioTree& ScenarioManager::getScenarioTree() const {

    return tree_; 
}

bool ScenarioManager::addEntry(const std::string& path, ScenarioEntry::EntryType type, const std::string& scenarioFile) {
    //std::cout << "----------" << path << "-------------" << std::endl;
    if(tree_.find(path) != NULL) {
        error_ = "[" + path +  "] is alreay exist.";
        return false;
    }

    std::string parentPath = path.substr(0, path.find_last_of('/')+1);
    std::string name = path.substr(parentPath.size());

    //std::cout << parentPath << std::endl;
    //std::cout << name << std::endl;

    ScenarioEntry* parent = tree_.find(parentPath);
    if(parent == NULL) {
        error_ = "Parent[" + parentPath + "] doesn't exist yet.";
        return false;
    }
    if(parent->type() != ScenarioEntry::GROUP) {
        error_ = "[" + parentPath + "] isn't ScenarioGroup.";
        return false;
    }

    if(type == ScenarioEntry::CASE) {
        ScenarioEntry* entry = new ScenarioCase(scenarioFile, name, parent);
        tree_.insert(parentPath, entry, error_);
    } else if(type == ScenarioEntry::GROUP) {
        ScenarioEntry* entry = new ScenarioGroup(name, parent);
        tree_.insert(parentPath, entry, error_);
    } else {
        assert(false);
    }

    //std::cout << "----------" << path << "-------------     OK" << std::endl;

    return true;
}
bool ScenarioManager::addScenario(const std::string& path, const std::string& scenarioFile) {
    return addEntry(path, ScenarioEntry::CASE, scenarioFile);
}
bool ScenarioManager::addGroup(const std::string& path) {
    return addEntry(path, ScenarioEntry::GROUP);
}

bool ScenarioManager::delEntry(const std::string& path, bool force) {
    if(tree_.find(path) == NULL) {
        error_ = "[" + path +  "] doesn't exist.";
        return false;
    }
    return tree_.erase(path, force, error_);
}

bool ScenarioManager::delScenario(const std::string& path) {
    return delEntry(path, false);
}
bool ScenarioManager::delGroup(const std::string& path, bool force) {
    return delEntry(path, force);
}
bool ScenarioManager::moveEntry(const std::string& oldPath, const std::string& newPath) {
    std::string newParentPath = newPath.substr(0, newPath.find_last_of("/")+1);
    //std::cout << newParentPath << std::endl;

    if(tree_.find(oldPath) == NULL) {
        error_ = "[" + oldPath + "] doesn't exist.";
        return false;
    }
    if(tree_.find(newPath) != NULL) {
        error_ = "[" + newPath + "] is already exist.";
        return false;
    }

    ScenarioEntry* newParent = tree_.find(newParentPath);
    if(newParent == NULL) {
        error_ = "[" + newParentPath + "] doesn't exist.";
        return false;
    }
    if(newParent->type() != ScenarioEntry::GROUP) {
        error_ = "[" + newParentPath + "] isn't group.";
        return false;
    }


    ScenarioEntry* entry = tree_.find(oldPath);
    ScenarioGroup* parent = dynamic_cast<ScenarioGroup*>(entry->parent());

    parent->remove(entry);

    ScenarioGroup* group = dynamic_cast<ScenarioGroup*>(newParent);
    group->add(entry);

    return true;
}
bool ScenarioManager::moveScenario(const std::string& oldPath, const std::string& newPath) {
    return moveEntry(oldPath, newPath);
}
bool ScenarioManager::moveGroup(const std::string& oldPath, const std::string& newPath) {
    return moveEntry(oldPath, newPath);
}

void ScenarioManager::writeConfig(const std::string& config) {

}
