
#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <string>
#include <istream>
#include <fstream>
#include "parse_exception.h"

#include <boost/tokenizer.hpp>
using namespace boost;

class Sentence {
    typedef tokenizer<escaped_list_separator<char> >::iterator iterator;
public:
    Sentence(const std::string& sentence);
    ~Sentence();

    void tokenize(const char* escapce, const char* separator, const char* quoteChar);

    bool hasNextToken() const;
    std::string nextToken();
    std::string currentToken() const;
    std::string getSentence() const { return _sentence; }

    iterator begin() const { return _tokens->begin(); }
    iterator end() const { return _tokens->end(); }

    Sentence& operator=(const Sentence& rhs);

private:
    std::string _sentence;
    tokenizer<escaped_list_separator<char> >* _tokens;
    iterator _current;


};

class Context {
public:
    Context(std::ifstream* is);
    Context();

    ~Context();

    bool hasNextSentence() const;
    Sentence nextSentence();
    Sentence currentSentence();

    void skipSentence(const std::string& nodeName) throw(ParseException);


private:
    bool _useFile;
    std::ifstream* _is;
    std::string _currentSentence;
    int _lineNumber;
};


#endif /* end of include guard */
