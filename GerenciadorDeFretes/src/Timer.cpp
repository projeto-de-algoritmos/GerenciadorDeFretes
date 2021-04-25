#include "Timer.hpp"
#include <SDL2/SDL.h>
#include <cfloat>

Timer::Timer():
_initial_ticks(SDL_GetTicks()),
_time_scale(1.0)
{

}

Timer::~Timer()
{

}

double_t Timer::getElapsedTime()
{
    if (_is_paused)
        _initial_ticks = SDL_GetTicks();

    return (double_t(SDL_GetTicks() - _initial_ticks) * _time_scale) / 1000.0;
}

double_t Timer::getTimeScale() const
{
    return _time_scale;
}

void Timer::setTimeScale(double_t time_scale)
{
    if (time_scale < DBL_EPSILON && time_scale > -DBL_EPSILON)
        pause();

    _time_scale = time_scale;
}

void Timer::reset()
{
    _initial_ticks = SDL_GetTicks();
}

void Timer::pause()
{
    _is_paused = true;
}

void Timer::resume()
{
    _is_paused = false;
}
