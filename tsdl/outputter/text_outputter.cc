
#include "tsdl/outputter/text_outputter.h"
#include "tsdl/scenario/scenario_result.h"

TextOutputter::TextOutputter(const std::string& file) : indentCount_(0){

    ofs_.open(file.c_str(), std::ios::trunc | std::ios::out);
}

TextOutputter::~TextOutputter() {

}

void TextOutputter::start(ScenarioResult* result) {
    if(result == NULL) {
        ofs_ << "Test Result:" << std::endl;
        return;
    }
    std::string indent;
    for(int i = 0; i < indentCount_; ++i) {
         indent += "  ";
    }
    ofs_ << indent << "------------ TestGroup<" << result->fullpath_ << ">   [";
    if(result->success_) {
        ofs_ << "SUCCESS.] ------------" << std::endl;
    } else {
        ofs_ << "FAILUER!!!.] ------------" << std::endl;
    }
    indentCount_++;
}

void TextOutputter::end(ScenarioResult* result) {
    if(result == NULL) {

        ofs_ << std::endl;
        return;
    }

    indentCount_--;
    std::string indent;
    for(int i = 0; i < indentCount_; ++i) {
         indent += "  ";
    }
    ofs_ << indent << "------------ TestGroup<" << result->fullpath_ << "> End" << std::endl;
}

void TextOutputter::write(ScenarioResult* result) {

    std::string indent;
    for(int i = 0; i < indentCount_; ++i) {
         indent += "  ";
    }

    ofs_ << indent << result->name_;
    if(result->success_) {
        ofs_ << " : OK" << std::endl;
    } else {
        ofs_ << " : NG" << "  error[" << result->errorStr_ << "]" << std::endl;
    }
}

