#include "program_node.h"
#include "parse_exception.h"
#include "context.h"
#include "init_node.h"
#include "setup_node.h"
#include "execute_list_node.h"
#include "teardown_node.h"
#include "condition_checker.h"

ProgramNode::ProgramNode() : Node()
{
    _initNode = NULL;
    _setupNode = NULL;
    _executeListNode = NULL;
    _teardownNode = NULL;
}

ProgramNode::~ProgramNode()
{
    delete _teardownNode;
    delete _executeListNode;
    delete _setupNode;
    delete _initNode;
}

void ProgramNode::parse(Context& context) throw ( ParseException )
{

    if(!context.hasNextSentence()) {
        throw ParseException("context error.");
    }

    _initNode = new InitNode(this);
    _setupNode = new SetupNode(this);
    _executeListNode = new ExecuteListNode(this);
    _teardownNode = new TeardownNode(this);

    try {
        _initNode->parse(context);
        _setupNode->parse(context);
        _executeListNode->parse(context);
        _teardownNode->parse(context);
    } catch (ParseException& e) {
        delete _teardownNode; 
        delete _executeListNode;
        delete _setupNode;
        delete _initNode;
        _initNode = NULL;
        _setupNode = NULL;
        _executeListNode = NULL;
        _teardownNode = NULL;
        throw e;
    }

    // Execute

}

void ProgramNode::execute() throw ( ExecuteException )  
{
    try {
        _initNode->execute();
        _setupNode->execute();
        _executeListNode->execute();
        _teardownNode->execute();
    } catch (ExecuteException& e) {
        std::cout << e.what() << std::endl;
    }

    return ;
}

void ProgramNode::setExecutorFactory(ExecutorFactory* factory)
{
    _executorFactory = factory;
}
Executor* ProgramNode::createExecutor(std::string name)
{
    return _executorFactory->create(name);
}

void ProgramNode::setConditionCheckerFactory(ConditionCheckerFactory* factory)
{
    _conditionCheckerFactory = factory;
}
ConditionChecker* ProgramNode::createConditionChecker(std::string name)
{
    return _conditionCheckerFactory->create(name);
}

