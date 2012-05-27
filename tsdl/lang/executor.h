
#ifndef TSDL_LANG_EXECUTOR_H
#define TSDL_LANG_EXECUTOR_H

#include <string>
#include "tsdl/lang/execute_exception.h"
#include <boost/any.hpp>

class Result {
public:
    Result() {}
    virtual ~Result() {}

    template <class T>
    const T getResult() const throw ( boost::bad_any_cast )
    { return boost::any_cast<T>(_result); }

    const std::type_info& type() const { return _result.type(); }

protected:
    boost::any _result;
};

class Executable {
public:
    virtual void execute() throw ( ExecuteException ) = 0;
};

class Node;
class Executor {
public:
    virtual Result* execute(std::string inputParam) = 0;
};


class ExecutorFactory {
public:
    virtual Executor* create(std::string name) = 0;
};

#endif /* end of include guard */
