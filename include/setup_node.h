
#ifndef SETUP_NODE_H_
#define SETUP_NODE_H_

#include "node.h"
#include "parse_exception.h"

class Context;
class ProgramNode;
class PostConditionNode;

class SetupNode : public Node {
public:
    SetupNode(ProgramNode* node);
    virtual ~SetupNode();

    virtual std::string getKey() const;
    virtual void parse(Context& context) throw(ParseException);
    virtual void execute() throw ( ExecuteException ) ;
private:

    std::string _inputParam;
    PostConditionNode* _postCondition;
    ProgramNode* _programNode;
};

#endif /* end of include guard */
