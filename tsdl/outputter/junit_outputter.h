
#ifndef TSDL_OUTPUTTER_JUNIT_OUTPUTTER_H
#define TSDL_OUTPUTTER_JUNIT_OUTPUTTER_H

#include "tsdl/outputter/text_outputter.h"

class JUnitOutputter : public TextOutputter {
public:
    JUnitOutputter(const std::string& file);
    virtual ~JUnitOutputter();

    virtual void start(ScenarioResult* result = NULL);
    virtual void end(ScenarioResult* result = NULL);
    virtual void write(ScenarioResult* result);

private:
};

#endif /* end of include guard */

