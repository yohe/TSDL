
#ifndef TSDL_LANG_INIT_NODE_H
#define TSDL_LANG_INIT_NODE_H

#include "tsdl/lang/node.h"
#include "tsdl/lang/parse_exception.h"


class Context;
class ProgramNode;
class InitNode : public Node {
public:
    InitNode(ProgramNode* node);
    virtual ~InitNode();

    virtual std::string getKey() const;
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

private:
    std::string _inputParam;
    ProgramNode* _programNode;
};

#endif /* end of include guard */
