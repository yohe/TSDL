
#ifndef TSDL_LANG_SETUP_NODE_H
#define TSDL_LANG_SETUP_NODE_H

#include "tsdl/lang/node.h"
#include "tsdl/lang/parse_exception.h"

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
    ProgramNode* _programNode;
    PostConditionNode* _postCondition;
};

#endif /* end of include guard */
