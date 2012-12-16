
#include "tsdl/outputter/junit_outputter.h"
#include "tsdl/scenario/scenario_result.h"

JUnitOutputter::JUnitOutputter(const std::string& file) : TextOutputter(file) , index_(0) {

}

JUnitOutputter::~JUnitOutputter() {

}

void JUnitOutputter::start(ScenarioResult* result) {
    if(result == NULL) {
        ofs_ << "<?xml version='1.0' encoding='UTF-8'?>" << std::endl;
        return;
    }

    if(indentCount_ == 0) {
        ofs_ << "<testsuites>" << std::endl;
    } else {
        std::string iso_timestamp = boost::posix_time::to_iso_extended_string(result->pt_);

        //ISO8601_DATETIME_PATTERN
        std::string timestamp = iso_timestamp.substr(0, iso_timestamp.find('.'));
        
        std::string indent;
        for(int i = 0; i < indentCount_; ++i) {
            indent += "  ";
        }
        ofs_ << indent 
             << "<testsuite tests=\"" << result->tests_
             << "\" failures=\"" << result->failures_ 
             << "\" errors=\"" << result->errors_
             << "\" name=\"" << result->fullpath_
             << "\" time=\"" << result->elapsedTime_
             << "\" timestamp=\"" << timestamp
             << "\" hostname=\"TSDL"
             << "\" package=\""
             << "\" id=\"" << index_ << "\" >" << std::endl;

        ofs_ << indent << indent << "<properties />" << std::endl;

        index_++;
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

        ofs_ << indent << indent << "<system-out />" << std::endl;
        ofs_ << indent << indent << "<system-err />" << std::endl;
        ofs_ << indent << "</testsuite>" << std::endl;
    }

}

void JUnitOutputter::write(ScenarioResult* result) {

    assert(indentCount_ == 2);

    std::string indent;
    for(int i = 0; i < indentCount_; ++i) {
        indent += "  ";
    }

    std::string::size_type pos = result->fullpath_.rfind(result->name_);

    ofs_ << indent
         << "<testcase name=\"" << result->name_ 
         << "\" classname=\"" << result->fullpath_
         << "\" time=\"" << result->elapsedTime_ << "\">" << std::endl;

    if(!result->success_) {
        ofs_ << indent << "  <failure message=\"" << result->errorStr_ << "\" type=\"\"/>" << std::endl;
    }
    ofs_ << indent << "</testcase>" << std::endl;
}

