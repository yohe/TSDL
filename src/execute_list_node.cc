
#include "executor.h"
#include "context.h"
#include "execute_list_node.h"
#include "program_node.h"
#include "post_condition_node.h"


ExecuteNode::ExecuteNode(ProgramNode* node) : Node(), _programNode(node)
{

}
ExecuteNode::~ExecuteNode() 
{

}

std::string ExecuteNode::getKey() const {
    return "execute";
}

void ExecuteNode::parse(Context& context) throw ( ParseException )
{
    Sentence sentence = context.currentSentence();
    sentence.tokenize(" :");

    if(sentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (execute) : \"execute\" was expected in a scnenario code, but was " + sentence.currentToken();
        throw ParseException(mes);
    }
    //std::cout << "execute" << std::endl;

    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (execute) : \"execute\" command format is \"execute [execute_name] [input_param] : [post_condition]\".";
        throw ParseException(mes);
    }
    _executeCommand = sentence.nextToken();
    //std::cout << "  " << _executeCommand << std::endl;
    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (execute) : \"execute\" command format is \"execute [execute_name] [input_param] : [post_condition]\".";
        throw ParseException(mes);
    }
    _inputParam = sentence.nextToken();
    //std::cout << "  " << _inputParam << std::endl;
    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (execute) : \"execute\" command format is \"execute [execute_name] [input_param] : [post_condition]\".";
        throw ParseException(mes);
    }
    _postCondition = new PostConditionNode(_programNode);
    _postCondition->parse(context);

    context.nextSentence();
}

void ExecuteNode::execute() throw ( ExecuteException ) 
{
    Executor* exe = _programNode->createExecutor(_executeCommand);
    Result* ret = exe->execute(_inputParam);

    _postCondition->setResult(ret);
    try {
        _postCondition->execute();
    } catch (ExecuteException& e) {
        std::string mes = _executeCommand + " execute error. [ " + e.what() + " ]";
        throw ExecuteException(mes);
    }

    return ;
}


ExecuteListNode::ExecuteListNode(ProgramNode* node) : Node(), _programNode(node) 
{

}

ExecuteListNode::~ExecuteListNode() 
{

}

std::string ExecuteListNode::getKey() const {
    return "execute";
}

void ExecuteListNode::parse(Context& context) throw ( ParseException )
{
    while(true) {
        ExecuteNode* node = new ExecuteNode(_programNode);
        try {
            node->parse(context);
        } catch (ParseException& e) {
            delete node;
            Sentence sentence = context.currentSentence();
            sentence.tokenize(" :");
            if(sentence.currentToken() == getKey()) {
                throw e;
                assert(false);
            }
            break;
        }

        _executeList.push_back(node);
    }
}

void ExecuteListNode::execute() throw ( ExecuteException ) 
{
    for(ExecuteNodeList::iterator ite = _executeList.begin();
        ite != _executeList.end();
        ++ite) {
        (*ite)->execute();
    }

}
