#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <cstdint>
#include <cmath>

class Timer
{
public:
    Timer();
    ~Timer();

    double_t getElapsedTime();
    double_t getTimeScale() const;
    void setTimeScale(double_t time_scale);
    void reset();

    void pause();
    void resume();

private:
    bool _is_paused = false;
    int32_t _initial_ticks;
    double_t _time_scale;
};

#endif