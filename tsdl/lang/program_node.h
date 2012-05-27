
#ifndef TSDL_LANG_PROGRAM_NODE_H
#define TSDL_LANG_PROGRAM_NODE_H

#include <string>
#include "tsdl/lang/node.h"

class ExecutorFactory;
class Executor;

class ConditionCheckerFactory;
class ConditionChecker;

class InitNode;
class SetupNode;
class TeardownNode;
class ExecuteListNode;
class ProgramNode : public Node {
public:
    ProgramNode();
    virtual ~ProgramNode();

    virtual std::string getKey() const { return ""; }
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

    void setExecutorFactory(ExecutorFactory* factory);
    Executor* createExecutor(std::string name);

    void setConditionCheckerFactory(ConditionCheckerFactory* factory);
    ConditionChecker* createConditionChecker(std::string name);
protected:
    InitNode* _initNode;
    SetupNode* _setupNode;
    TeardownNode* _teardownNode;
    ExecuteListNode* _executeListNode;
    ExecutorFactory* _executorFactory;
    ConditionCheckerFactory* _conditionCheckerFactory;
};

#endif /* end of include guard */
