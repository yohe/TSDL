
#ifndef TSDL_LANG_PARSE_EXCEPTION_H
#define TSDL_LANG_PARSE_EXCEPTION_H

#include <string>
#include <stdexcept>

class ParseException : public std::invalid_argument {
public:
    ParseException(const std::string& message) : std::invalid_argument(message) {}
};

#endif /* end of include guard */
