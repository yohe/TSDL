
#include "context.h"
#include "setup_node.h"
#include "program_node.h"
#include "post_condition_node.h"

SetupNode::SetupNode(ProgramNode* node) : Node() , _programNode(node), _postCondition(NULL)
{

}

SetupNode::~SetupNode() 
{

    delete _postCondition;
}

std::string SetupNode::getKey() const {
    return "setup";
}
void SetupNode::parse(Context& context) throw ( ParseException )
{
    Sentence sentence = context.currentSentence();
    sentence.tokenize("", " ", "\"");

    if(sentence.currentToken() == "") {
        throw ParseException("ScenarioError (setup) : Scenario code is empty.");
    }


    if(sentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (setup) : \"setup\" was expected in a scnenario code, but was " + sentence.currentToken();
        throw ParseException(mes);
    }
    //std::cout << "setup" << std::endl;

    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (setup) : \"setup\" command format is \"setup [inpu_param] : [post_condition]\".";
        throw ParseException(mes);
    }
    _inputParam = sentence.nextToken();
    //std::cout << "  " << _inputParam << std::endl;
    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (setup) : \"setup\" command format is \"setup [inpu_param] : [post_condition]\".";
        throw ParseException(mes);
    }
    _postCondition = new PostConditionNode(_programNode);
    _postCondition->parse(context);

    context.nextSentence();
}

void SetupNode::execute() throw ( ExecuteException )  
{
    Executor* exe = _programNode->createExecutor(getKey());
    Result* ret = NULL;
    try {
        ret = exe->execute(_inputParam);
        _postCondition->setResult(ret);
        _postCondition->execute();
    } catch (ExecuteException& e) {
        delete exe;
        delete ret;
        throw e;
    }

    delete exe;
    delete ret;
    //std::cout << "setup execute end." << std::endl;
    return ;
}
