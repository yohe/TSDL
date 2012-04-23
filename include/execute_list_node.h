
#ifndef EXECUTE_LIST_NODE_H_
#define EXECUTE_LIST_NODE_H_

#include <list>

#include "node.h"
#include "parse_exception.h"

class Context;
class ProgramNode;
class PostConditionNode;

class ExecuteNode : public Node {
public:
    ExecuteNode(ProgramNode* node);
    virtual ~ExecuteNode();

    virtual std::string getKey() const;
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

private:

    std::string _executeCommand;
    std::string _inputParam;
    ProgramNode* _programNode;
    PostConditionNode* _postCondition;
    //Executor* _executor;

};


class ExecuteListNode : public Node {
public:
    ExecuteListNode(ProgramNode* node);
    virtual ~ExecuteListNode();

    virtual std::string getKey() const;
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

private:
    typedef std::list<ExecuteNode*> ExecuteNodeList;
    ExecuteNodeList _executeList;
    ProgramNode* _programNode;

};

#endif /* end of include guard */
