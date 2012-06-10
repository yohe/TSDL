
#include "tsdl/scenario/scenario_timer.h"
using namespace boost::posix_time;

ptime Timer::now() const {
    return second_clock::local_time();
}

CountUpTimer::CountUpTimer() : setTime_(), pause_(false), pauseTime_(){
}

void CountUpTimer::set() {
    setTime_ = now();
    pause_ = false;
}

time_duration CountUpTimer::elapsed() const {
    if(!isPause())
        return (now() - setTime_);
    else
        return (pauseTime_ - setTime_);
}

time_duration CountUpTimer::pause() {
    time_duration elapsedPTime(0,0,0,0);
    if(!isPause()){
        pauseTime_ = now();
    } else {
        elapsedPTime = now() - pauseTime_;
        std::cout << elapsedPTime.total_seconds() << std::endl;
        setTime_ += elapsedPTime;
    }
    pause_ = !pause_;
    return elapsedPTime;
}

void CountDownTimer::set(long milisec){
    setTime_ = (countUpTimer.now().time_of_day() + milliseconds(milisec));
    countUpTimer.set();
}

long CountDownTimer::remainingTime(void) const {
    time_duration result = setTime_ - countUpTimer.elapsed();
    return (result.is_negative() ? 0 : result.total_milliseconds());
}

bool CountDownTimer::checkTimeOver(void) const {
    return (remainingTime() > 0);
}

time_duration CountDownTimer::pause(void){
    return countUpTimer.pause();
}

