
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
             << "\" name=\"" << result->fullpath_ 
             << "\" time=\"" << result->elapsedTime_ << "\">" << std::endl;
    } else {
        std::string indent;
        for(int i = 0; i < indentCount_; ++i) {
            indent += "  ";
        }
        ofs_ << indent << "<testsuite tests=\"" << result->tests_ << "\" failures=\""
             << result->failures_ << "\" errors=\"" << result->errors_
             << "\" name=\"" << result->fullpath_
             << "\" time=\"" << result->elapsedTime_ << "\">" << std::endl;
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
        std::string indent;
        for(int i = 0; i < indentCount_; ++i) {
            indent += "  ";
        }
        ofs_ << indent << "</testsuite>" << std::endl;
    }

}

void JUnitOutputter::write(ScenarioResult* result) {
    std::string indent;
    for(int i = 0; i < indentCount_; ++i) {
        indent += "  ";
    }

    ofs_ << indent << "<testcase name=\"" << result->name_ << "\" classname=\"\" status=\"\" time=\"" << result->elapsedTime_ << "\">" << std::endl;
    if(!result->success_) {
        ofs_ << indent << "  <failure message=\"" << result->errorStr_ << "\" type=\"\"/>" << std::endl;
    }
    ofs_ << indent << "</testcase>" << std::endl;
}

