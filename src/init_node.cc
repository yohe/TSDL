
#include "context.h"
#include "init_node.h"
#include "program_node.h"
#include <sstream>

InitNode::InitNode(ProgramNode* node) : Node() , _programNode(node)
{

}

InitNode::~InitNode() 
{

}

std::string InitNode::getKey() const {
    return "init";
}
void InitNode::parse(Context& context) throw ( ParseException )
{
    Sentence sentence = context.currentSentence();
    sentence.tokenize(" ");

    if(sentence.currentToken() == "") {
        throw ParseException("ScenarioError (init) : Scenario code is empty.");
    }


    if(sentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (init) : \"init\" was expected in a scnenario code, but was " + sentence.currentToken();
        throw ParseException(mes);
    }
//    std::cout << "init" << std::endl;

    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (init) : \"init\" command format is \"init [inpu_param]\".";
        throw ParseException(mes);
    }
    _inputParam = sentence.nextToken();
 //   std::cout << "  " << _inputParam << std::endl;

    context.nextSentence();
}

void InitNode::execute() throw ( ExecuteException )  
{
    Executor* exe = _programNode->createExecutor(getKey());
    Result* tmp = exe->execute(_inputParam);

    InitResult* ret = dynamic_cast<InitResult*>(tmp);
    int errorCode = ret->getResult<int>();

    if(errorCode != 0) {
        std::stringstream ss;
        ss << "ExecuteException: init ErrorCode = " << errorCode;
        throw ExecuteException(ss.str());
    }

    //std::cout << "init execute end." << std::endl;
    return ;
}
