
#include <sstream>

#include "tsdl/lang/executor.h"
#include "tsdl/lang/context.h"
#include "tsdl/lang/program_node.h"
#include "tsdl/lang/execute_list_node.h"
#include "tsdl/lang/post_condition_node.h"
#include "tsdl/lang/condition_checker.h"

ConditionNode::ConditionNode(ProgramNode* node) : Node(), _programNode(node), _conditionCommand(), _inputParam(), _result(NULL)
{

}

ConditionNode::~ConditionNode()
{
}

std::string ConditionNode::getKey() const 
{
    return "cond";
}

void ConditionNode::parse(Context& context) throw ( ParseException )
{

}
void ConditionNode::parse(Sentence& sentence) throw ( ParseException )
{
    if(sentence.currentToken() == "") {
        throw ParseException("ScenarioError (cond) : Scenario code is empty.");
    }

    if(sentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (cond) : \"cond\" was expected in a scnenario code, but was " + sentence.currentToken();
        throw ParseException(mes);
    }

    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (cond) : \"post_condition\" format is \"cond [condition_name] [input_param]\".";
        throw ParseException(mes);
    }

    _conditionCommand = sentence.nextToken();
    if(_conditionCommand == "null") {
        return;
    }

    //std::cout << "    " << _conditionCommand << std::endl;
    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (cond) : \"post_condition\" format is \"cond [condition_name] [input_param]\".";
        throw ParseException(mes);
    }
    _inputParam = sentence.nextToken();
    //std::cout << "    " << _inputParam << std::endl;

}

void ConditionNode::execute() throw ( ExecuteException ) 
{
    if(_conditionCommand == "null") {
        return;
    }

    ConditionChecker* checker = _programNode->createConditionChecker(_conditionCommand);
    if(checker == NULL) {
        std::string mes = "ConditionChecker create error. ConditionName = " + _conditionCommand;
        throw ExecuteException(mes);
    }

    try {
        std::string param = _programNode->variableToValue(_inputParam);
        bool ret = checker->check(_result, param);
        if(ret == false) { 
            std::string mes = "condition pass error. ConditionName = " + _conditionCommand + " : condition param = " + _inputParam;
            mes += "  Error[" + checker->getError() + "]";
            delete checker;
            throw ExecuteException(mes);
        }
        delete checker;
    } catch ( boost::bad_any_cast& e) {
        delete checker;
        std::stringstream ss;
        ss << "condition check error. [" << e.what() << "]" << std::endl;
        ss << "                       ConditionName = " << _conditionCommand << " : condition param = " << _inputParam;
        throw ExecuteException(ss.str());
    }

}

void ConditionNode::setResult(Result* result) {
    _result = result;
}

PostConditionNode::PostConditionNode(ProgramNode* node) : Node(), _programNode(node), _result(NULL)
{

}

PostConditionNode::~PostConditionNode()
{
    for(ConditionList::iterator ite = _conditionList.begin();   
        ite != _conditionList.end();
        ++ite) {

        delete *ite;
    }
    _conditionList.clear();

}

std::string PostConditionNode::getKey() const 
{
    return "cond";
}

void PostConditionNode::parse(Context& context) throw ( ParseException )
{
    Sentence sentence = context.currentSentence();
    sentence.tokenize("", ":", "");
    sentence.nextToken();

    // remove the leading spaces.
    std::string tmp = sentence.currentToken();
    tmp = tmp.erase(0, tmp.find_first_not_of(" "));

    Sentence condSentence(tmp);
    condSentence.tokenize("", " ", "\"");

    //for(tokenizer<escaped_list_separator<char> >::iterator ite = condSentence.begin(); ite != condSentence.end(); ++ite) {
    //    std::cout << "<" << *ite << ">" << std::endl;
    //}

    if(condSentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (PostCondition) : \"cond\" was expected in a scnenario code, but was " + condSentence.currentToken();
        throw ParseException(mes);
    }

    while(condSentence.currentToken() == getKey()) {
        //std::cout << "  " << condSentence.currentToken() << std::endl;
        ConditionNode* cond = new ConditionNode(_programNode);
        try {
            cond->parse(condSentence);
        } catch (ParseException& e) {
            throw;
        }

        _conditionList.push_back(cond);

        if(condSentence.hasNextToken()) {
            if( condSentence.nextToken() == "and") {
                condSentence.nextToken();
            } else {
                std::string mes = "SecnarioError (Postcondition) : syntax error, before " + condSentence.currentToken();
                throw ParseException(mes);
            }
        }
    }
}

void PostConditionNode::execute() throw ( ExecuteException ) 
{
    for(ConditionList::iterator ite = _conditionList.begin();   
        ite != _conditionList.end();
        ++ite) {
        (*ite)->setResult(_result);
        (*ite)->execute();
    }

}

void PostConditionNode::setResult(Result* result) {
    _result = result;
}
