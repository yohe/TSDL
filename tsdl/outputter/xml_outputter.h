
#ifndef TSDL_XML_OUTPUTTER_H
#define TSDL_XML_OUTPUTTER_H

#include "tsdl/outputter/text_outputter.h"

class XmlOutputter : public TextOutputter {
public:
    XmlOutputter(const std::string& file);
    virtual ~XmlOutputter();

    virtual void start(ScenarioResult* result = NULL);
    virtual void end(ScenarioResult* result = NULL);
    virtual void write(ScenarioResult* result);
};

#endif /* end of include guard */
