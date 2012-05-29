
#include "tsdl/outputter/junit_outputter.h"
#include "tsdl/scenario/scenario_result.h"

JUnitOutputter::JUnitOutputter(const std::string& file) : TextOutputter(file) {

}

JUnitOutputter::~JUnitOutputter() {

}

void JUnitOutputter::start(ScenarioResult* result) {
    if(result == NULL) {
        ofs_ << "<?xml version='1.0' encoding='UTF-8'?>" << std::endl;
        return;
    }

    if(indentCount_ == 0) {
        ofs_ << "<testsuites tests=\"" << result->tests_ << "\" failures=\""
             << result->failures_ << "\" errors=\"" << result->errors_
             << "\" name=\"" << result->fullpath_ << "\">" << std::endl;
    } else {
        ofs_ << "<testsuite tests=\"" << result->tests_ << "\" failures=\""
             << result->failures_ << "\" errors=\"" << result->errors_
             << "\" name=\"" << result->fullpath_ << "\">" << std::endl;
    }

    indentCount_++;
}

void JUnitOutputter::end(ScenarioResult* result) {
    if(result == NULL) {
        ofs_ << std::endl;
        return;
    }

    indentCount_--;

    if(indentCount_ == 0) {
        ofs_ << "</testsuites>" << std::endl;
    } else {
        ofs_ << "</testsuite>" << std::endl;
    }

}

void JUnitOutputter::write(ScenarioResult* result) {
    ofs_ << "<testcase name=\"" << result->name_ << "\" classname=\"\" status=\"\" time=\"\">" << std::endl;
    if(!result->success_) {
        ofs_ << "<failure message=\"" << result->errorStr_ << "\" type=\"\"/>" << std::endl;
    }
    ofs_ << "</testcase>" << std::endl;
}

