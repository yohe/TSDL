
#ifndef TSDL_FORMAT_OUTPTTER_H
#define TSDL_FORMAT_OUTPTTER_H

#include <iostream>

class ScenarioResult;

class FormatOutputter {
public:
    FormatOutputter();
    virtual ~FormatOutputter();

    virtual void start(ScenarioResult* result = NULL) = 0;
    virtual void end(ScenarioResult* result = NULL) = 0;
    virtual void write(ScenarioResult* result) = 0;
};

#endif /* end of include guard */
