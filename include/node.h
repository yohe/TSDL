
#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "parse_exception.h"
#include "executor.h"

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
