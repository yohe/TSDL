
#include "context.h"
#include "teardown_node.h"
#include "program_node.h"
#include "post_condition_node.h"

TeardownNode::TeardownNode(ProgramNode* node) : Node() , _programNode(node), _postCondition(NULL)
{

}

TeardownNode::~TeardownNode() 
{

    delete _postCondition;
}

std::string TeardownNode::getKey() const {
    return "teardown";
}
void TeardownNode::parse(Context& context) throw ( ParseException )
{
    Sentence sentence = context.currentSentence();
    sentence.tokenize("", " ", "\"");

    if(sentence.currentToken() == "") {
        throw ParseException("ScenarioError (teardown) : Scenario code is empty.");
    }


    if(sentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (teardown) : \"teardown\" was expected in a scnenario code, but was " + sentence.currentToken();
        throw ParseException(mes);
    }
    //std::cout << "teardown" << std::endl;

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

void TeardownNode::execute() throw ( ExecuteException )  
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
    return ;
}
