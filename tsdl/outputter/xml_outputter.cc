
#include "tsdl/outputter/xml_outputter.h"
#include "tsdl/scenario/scenario_result.h"

XmlOutputter::XmlOutputter(const std::string& file) : TextOutputter(file) {

}

XmlOutputter::~XmlOutputter() {

}

void XmlOutputter::start(ScenarioResult* result) {
    if(result == NULL) {
        ofs_ << "<?xml version='1.0' encoding='UTF-8'?>" << std::endl;
        ofs_ << "<TestResults>" << std::endl;
        return;
    }
    ofs_ << "<TestGroup name=\"" << result->fullpath_ << "\" state=";
    if(result->success_) {
        ofs_ << "\"success\"";
    } else {
        ofs_ << "\"failure\"";
    }

    ofs_ << ">" << std::endl;
}

void XmlOutputter::end(ScenarioResult* result) {

    if(result == NULL) {
        ofs_ << "</TestResults>" << std::endl;
        return;
    }
    ofs_ << "</TestGroup>" << std::endl;
}

void XmlOutputter::write(ScenarioResult* result) {
    ofs_ << "<TestCase name=\"" << result->fullpath_ << "\" state=";
    if(result->success_) {
        ofs_ << "\"success\"";
    } else {
        ofs_ << "\"faulure\"";
    }
    ofs_ << ">" << std::endl;
    ofs_ << "<ErrorMessage>" << result->errorStr_ << "</ErrorMessage>" << std::endl;
    ofs_ << "</TestCase>" << std::endl;
}

