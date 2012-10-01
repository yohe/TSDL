
#include "tsdl/lang/context.h"
#include "tsdl/lang/parse_exception.h"

Context::Context(std::ifstream* is) : _useFile(true), _is(is), _currentSentence(""), _lineNumber(0)
{
    nextSentence();
}

Context::Context() : _useFile(false), _is(NULL), _currentSentence(""), _lineNumber(0)
{
    assert(false);
}

Context::~Context()
{
}

bool Context::hasNextSentence() const
{
    if(!_is->good() || _is->eof()) {
        return false;
    }

    return true;
}


void Context::skipSentence(const std::string& nodeName) throw(ParseException) {
    if(nodeName.find_first_of(_currentSentence.c_str(), 0, _currentSentence.size()) == std::string::npos) {
        throw ParseException("Warning: " + nodeName + " is expected. but was " + _currentSentence);
    }

    nextSentence();
}

Sentence::Sentence(const std::string& sentence) : _sentence(sentence), _sep(), _tokens(NULL), _current()
{
}

Sentence::~Sentence()
{
    delete _tokens;
}

Sentence Context::nextSentence() {
    _currentSentence = "";
    while(_currentSentence.empty() && hasNextSentence()) {
        std::string line;
        std::getline(*_is, line);
        if(line.empty() || line.at(0) == '#') {
            continue;
        }
        _currentSentence = line;
    }

    return Sentence(_currentSentence);
}

Sentence Context::currentSentence() {
    return Sentence(_currentSentence);
}
void Sentence::tokenize(const char* escape, const char* separator, const char* quoteChar) {

    boost::escaped_list_separator<char> sep(escape, separator, quoteChar);
    tokenize(_sep);
}
void Sentence::tokenize(const boost::escaped_list_separator<char>& sep) {
    if(_tokens != NULL) {
        delete _tokens;
        _tokens = NULL;
    }

    _sep = sep;
    _tokens = new boost::tokenizer<escaped_list_separator<char> >(_sentence, sep);
    _current = _tokens->begin();
}

std::string Sentence::nextToken() {

    if(_tokens == NULL || _current == _tokens->end()) {
        return "";
    }
    std::string currentToken = *_current;
    _current++;

    if(_current == _tokens->end()) {
        std::string mes = _sentence + " don't have next token after " + currentToken;
        throw ParseException(mes);
    }

    return *_current;
}

std::string Sentence::currentToken() const {

    if(_tokens == NULL || _current == _tokens->end()) {
        return "";
    }
    return *_current;
}

bool Sentence::hasNextToken() const {
    iterator ite = _current;
    ite++;
    return (ite) != _tokens->end();
}

Sentence& Sentence::operator=(const Sentence& rhs) {
    _sentence = rhs._sentence;
    tokenize(rhs._sep);

    return *this;
}
