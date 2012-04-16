
#ifndef PARSE_EXCEPTION_H_
#define PARSE_EXCEPTION_H_

#include <string>
#include <stdexcept>

class ParseException : public std::invalid_argument {
public:
    ParseException(const std::string& message) : std::invalid_argument(message) {}
};

#endif /* end of include guard */
