
#ifndef TSDL_LANG_NODE_H
#define TSDL_LANG_NODE_H

#include <string>
#include "tsdl/lang/parse_exception.h"
#include "tsdl/lang/executor.h"

class Context;

class Node : public Executable {
public:
    Node() {}
    virtual ~Node() {}

    virtual std::string getKey() const = 0;
    virtual void parse(Context& context) throw ( ParseException ) = 0;
    virtual void execute() throw ( ExecuteException ) = 0;

private:
};
#endif /* end of include guard */
