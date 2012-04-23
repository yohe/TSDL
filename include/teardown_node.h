
#ifndef TERMINATE_NODE_H_
#define TERMINATE_NODE_H_

#include "node.h"
#include "parse_exception.h"

class Context;
class ProgramNode;
class PostConditionNode;

class TeardownNode : public Node {
public:
    TeardownNode(ProgramNode* node);
    virtual ~TeardownNode();

    virtual std::string getKey() const;
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

private:
    std::string _inputParam;
    ProgramNode* _programNode;
    PostConditionNode* _postCondition;
};

#endif /* end of include guard */
