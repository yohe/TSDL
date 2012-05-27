
#include "tsdl/outputter/xml_outputter.h"
#include "tsdl/scenario/scenario_result.h"

XmlOutputter::XmlOutputter(const std::string& file) : TextOutputter(file) {

    start();
}

XmlOutputter::~XmlOutputter() {

    end();
}

void XmlOutputter::start(ScenarioResult* result) {
    ofs_ << "<?xml version='1.0' encoding='UTF-8'?>" << std::endl;
}
void XmlOutputter::end(ScenarioResult* result) {

}

void XmlOutputter::write(ScenarioResult* result) {

}


