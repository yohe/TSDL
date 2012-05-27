
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
    ofs_ << "-------------------- Start (" << result->fullpath_ << ") --------------------" << std::endl;
    indentCount_++;
}

void TextOutputter::end(ScenarioResult* result) {
    if(result == NULL) {

        ofs_ << std::endl;
        return;
    }

    ofs_ << "-------------------- end (" << result->fullpath_ << ") --------------------" << std::endl;
    indentCount_--;
}

void TextOutputter::write(ScenarioResult* result) {

    std::string indent;
    for(int i = 0; i < indentCount_; ++i) {
         indent += "\t";
    }

    ofs_ << indent << result->name_;
    if(result->success_) {
        ofs_ << " : OK" << std::endl;
    } else {
        ofs_ << " : NG" << "  error[" << result->errorStr_ << "]" << std::endl;
    }
}

