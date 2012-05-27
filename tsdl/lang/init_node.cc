
#include "tsdl/lang/context.h"
#include "tsdl/lang/init_node.h"
#include "tsdl/lang/program_node.h"
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
    sentence.tokenize("", " ", "\"");

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
    Result* ret = NULL;
    try {
        ret = exe->execute(_inputParam);

    } catch (ExecuteException& e) {
        delete exe;
        delete ret;
        throw e;
    }

    delete exe;
    delete ret;

    //std::cout << "init execute end." << std::endl;
    return ;
}
