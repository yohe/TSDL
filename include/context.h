
#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <string>
#include <istream>
#include <fstream>
#include "parse_exception.h"

#include <boost/tokenizer.hpp>
using namespace boost;

class Sentence {
public:
    Sentence(const std::string& sentence);

    void tokenize(const char* separator);

    bool hasNextToken() const;
    std::string nextToken();
    std::string currentToken() const;
    std::string getSentence() const { return _sentence; }

    //iterator begin() const;
    //iterator end() const;

private:
    std::string _sentence;
    tokenizer<char_separator<char> >* _tokens;
    typedef tokenizer<char_separator<char> >::iterator iterator;
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
