
#ifndef TSDL_TEXT_OUTPUTTER_H
#define TSDL_TEXT_OUTPUTTER_H

#include <fstream>

#include "tsdl/outputter/format_outputter.h"

class TextOutputter : public FormatOutputter {
public:
    TextOutputter(const std::string& file);
    virtual ~TextOutputter();

    virtual void start(ScenarioResult* result = NULL);
    virtual void end(ScenarioResult* result = NULL);
    virtual void write(ScenarioResult* result);

protected:
    int indentCount_;
    std::ofstream ofs_;
};

#endif /* end of include guard */
