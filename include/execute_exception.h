
#ifndef EXECUTE_EXCEPTION_H_
#define EXECUTE_EXCEPTION_H_

#include <string>
#include <stdexcept>

class ExecuteException : public std::invalid_argument {
public:
    ExecuteException(const std::string& message) : std::invalid_argument(message) {}
};

#endif /* end of include guard */
