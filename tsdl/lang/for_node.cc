
#include "tsdl/lang/context.h"
#include "tsdl/lang/execute_list_node.h"
#include "tsdl/lang/program_node.h"
#include "tsdl/lang/for_node.h"

ForNode::ForNode(ProgramNode* node) : _programNode(node) {
}

ForNode::~ForNode() {
}

void ForNode::parse(Context& context) throw ( ParseException ) {
    Sentence sentence = context.currentSentence();
    sentence.tokenize("", " ,", "\"");

    if(sentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (for) : \"for\" was expected in a scnenario code, but was " + sentence.currentToken();
        throw ParseException(mes);
    }

    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (for) : \"for\" command format is \"for <variable name> in <input_param>,[input_param]...";
        throw ParseException(mes);
    }
    _variableName = sentence.nextToken();
    if(!_programNode->setVariable(_variableName, "")) {
        std::string mes = "Variable Error : redefinition of " + _variableName;
        throw ParseException(mes);
    }
    //std::cout << "  " << _variableName << std::endl;
    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (for) : \"for\" command format is \"for <variable name> in <input_param>,[input_param]...";
        throw ParseException(mes);
    }
    if(sentence.nextToken() != "in") {
        std::string mes = "ScenarioError (for) : \"for\" command format is \"for <variable name> in <input_param>,[input_param]...";
        throw ParseException(mes);
    }
    if(!sentence.hasNextToken()) {
        std::string mes = "ScenarioError (for) : \"for\" command format is \"for <variable name> in <input_param>,[input_param]...";
        throw ParseException(mes);
    }
    _params.push_back(sentence.nextToken());
    while(sentence.hasNextToken()) {
        _params.push_back(sentence.nextToken());
    }

    context.nextSentence();

    _executeListNode = new ExecuteListNode(_programNode);
    _forEndNode = new ForEndNode();
    try {
        _executeListNode->parse(context);
        _forEndNode->parse(context);
    } catch (ParseException& e) {
        delete _executeListNode;
        delete _forEndNode;
        _executeListNode = NULL;
        _forEndNode = NULL;
        throw;
    }

}

void ForNode::execute() throw ( ExecuteException ) {
    std::vector<std::string>::iterator it = _params.begin();
    for(; it != _params.end(); it++) {
        _programNode->setVariable(_variableName, *it);
        _executeListNode->execute();
        _programNode->unsetVariable(_variableName);
    }
    _forEndNode->execute();
    _programNode->unsetVariable(_variableName);
}

ForEndNode::ForEndNode() {
}
ForEndNode::~ForEndNode() {
}
void ForEndNode::parse(Context& context) throw ( ParseException ) {
    Sentence sentence = context.currentSentence();
    sentence.tokenize("", " ,", "\"");

    if(sentence.currentToken() != getKey()) {
        std::string mes = "ScenarioError (forend) : \"forend\" was expected in a scnenario code, but was " + sentence.currentToken();
        throw ParseException(mes);
    }
    context.nextSentence();
}
void ForEndNode::execute() throw ( ExecuteException ) {
}
