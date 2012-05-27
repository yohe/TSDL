
#ifndef TSDL_LANG_POST_CONDITHON_NODE_H
#define TSDL_LANG_POST_CONDITHON_NODE_H

#include <list>
#include "tsdl/lang/node.h"
#include "tsdl/lang/parse_exception.h"

class Context;
class ProgramNode;

class ConditionNode : public Node {
public:
    ConditionNode(ProgramNode* node);
    ~ConditionNode();

    virtual std::string getKey() const;
    virtual void parse(Context& context) throw ( ParseException );
    virtual void parse(Sentence& sentence) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

    void setResult(Result* result);
protected:
    ProgramNode* _programNode;
    //Executor* _executor;
    std::string _conditionCommand;
    std::string _inputParam;
    Result* _result;
};

class PostConditionNode : public Node {
public:
    PostConditionNode(ProgramNode* node);
    ~PostConditionNode();

    virtual std::string getKey() const;
    virtual void parse(Context& context) throw ( ParseException );
    virtual void execute() throw ( ExecuteException ) ;

    void setResult(Result* result);
protected:
    typedef std::list<ConditionNode*> ConditionList;
    ConditionList _conditionList;
    ProgramNode* _programNode;
    //Executor* _executor;
    Result* _result;

};

#endif /* end of include guard */
