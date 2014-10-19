
#ifndef TSDL_LANG_FOR_NODE_H
#define TSDL_LANG_FOR_NODE_H

#include <string>
#include <vector>
#include "tsdl/lang/node.h"

class ProgramNode;
class ExecuteListNode;

class ForEndNode : public Node {
public:
    ForEndNode();
    virtual ~ForEndNode();

    virtual std::string getKey() const { return "forend"; }
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

protected:
};

class ForNode : public Node {
public:
    ForNode(ProgramNode* node);
    virtual ~ForNode();

    virtual std::string getKey() const { return "for"; }
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

protected:
    std::string _variableName;
    std::vector<std::string> _params;
    ProgramNode* _programNode;
    ExecuteListNode* _executeListNode;
    ForEndNode* _forEndNode;
};

#endif /* end of include guard */

