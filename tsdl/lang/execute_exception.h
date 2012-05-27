
#ifndef TSDL_LANG_EXECUTE_EXCEPTION_H
#define TSDL_LANG_EXECUTE_EXCEPTION_H

#include <string>
#include <stdexcept>

class ExecuteException : public std::invalid_argument {
public:
    ExecuteException(const std::string& message) : std::invalid_argument(message) {}
};

#endif /* end of include guard */
