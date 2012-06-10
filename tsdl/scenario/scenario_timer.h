#ifndef TSDL_SCENARIO_SCENARIO_TIMER_H
#define TSDL_SCENARIO_SCENARIO_TIMER_H

#include <boost/date_time.hpp>
using namespace boost::posix_time;

class Timer {
public:
    
    Timer() {}
    virtual ~Timer() {}

    ptime now() const;

private:

};

class CountUpTimer : public Timer {

    /**
     * カウントアップタイマ
     * set()後からの経過時間を測る機能
     */

public:
    CountUpTimer();

    /**
     * カウントアップを開始します
     */
    void set();

    /**
     * 経過時間をミリ秒で返します
     * @return 経過時間
     */
    time_duration elapsed() const; 

    /**
     * カウントアップを一時停止します or 再開します
     * @return Pauseしていた時間間隔を返します
     */
    time_duration pause();

    /**
     * Pause中かどうかを返します
     * @return true 停止状態 / false 動作状態
     */
    bool isPause() const {
        return pause_;
    }

protected:
    // 設定時刻
    ptime setTime_;
    // 一時停止指定時間
    bool pause_;
    ptime pauseTime_;
};


class CountDownTimer{

    /**
     * カウントダウンタイマ
     * 指定した長さの時間でカウントダウンします
     * 
     */

public:
    CountDownTimer();

    /**
     * カウントダウンの時間のを指定します。
     * @param Time 測る時間を設定(単位は秒) 例）10.5秒後であれば 10.5を指定
     */
    void set(long milisec);

    /**
     * 残りの時間を取得します
     * @return 残り時間
     */
    long remainingTime(void) const;

    /**
     * 指定時間を経過いないかを返します
     * @return true 経過していない / false 経過している 
     */
    bool checkTimeOver(void) const;

    /**
     * カウントダウンを一時停止 or 再開します。
     * @return Pause期間の時間
     */
    time_duration pause(void);

    /**
     * Pause中かどうかを返します。
     * @return true 停止状態 / false 動作状態
     */
    bool isPause(void) const {
        return countUpTimer.isPause();
    }

    ptime now() const { return countUpTimer.now(); }

protected:
    time_duration setTime_;
    ptime pauseTime_;
    CountUpTimer countUpTimer;
};

#endif
