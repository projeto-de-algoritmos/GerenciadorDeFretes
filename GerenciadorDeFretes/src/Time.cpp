#include <string>
#include <stdexcept>
#include <cctype>

#include "Time.hpp"

Time::Time(const std::string & str)
{
    if (str.size() != 8 || !std::isdigit(str[0]) || !std::isdigit(str[1]) ||
      !std::isdigit(str[3]) || !std::isdigit(str[4]) || !std::isdigit(str[6]) ||
      !std::isdigit(str[7]) || str[2] != ':' || str[5] != ':')
        throw std::runtime_error("Attempt to construct a new Time object with invalid string: " + str);
    
    uint16_t hour = uint16_t(str[0] - '0') * 10 + uint16_t(str[1] - '0');
    uint16_t minute = uint16_t(str[3] - '0') * 10 + uint16_t(str[4] - '0');
    uint16_t second = uint16_t(str[6] - '0') * 10 + uint16_t(str[7] - '0');
    setHour(hour);
    setMinute(minute);
    setSecond(second);
}

Time::Time(const uint16_t hour, const uint16_t minute, const uint16_t second):
_seconds(int64_t(hour) * 3600 + int64_t(minute) * 60 + int64_t(second))
{

}

std::string Time::toString() const noexcept
{
    return std::to_string(getHour()) + ":" + std::to_string(getMinute()) + ":" + std::to_string(getSecond());
}

Time::Time(const int64_t seconds):
_seconds(seconds)
{

}

Time::~Time()
{

}

int64_t Time::toSeconds() const noexcept
{
    return _seconds;
}

uint16_t Time::getHour() const noexcept
{
    return _seconds / 3600LL;
}

void Time::setHour(const uint16_t hour) noexcept
{
    _seconds = int64_t(hour) * 3600LL + int64_t(getMinute()) * 60LL + int64_t(getSecond());
}

uint16_t Time::getMinute() const noexcept
{
    return (_seconds % 3600LL) / 60LL;
}

void Time::setMinute(const uint16_t minute) noexcept
{
    _seconds = int64_t(getHour()) * 3600LL + int64_t(minute) * 60LL + int64_t(getSecond());
}

uint16_t Time::getSecond() const noexcept
{
    return ((_seconds % 3600LL) % 60LL);
}

void Time::setSecond(const uint16_t second) noexcept
{
    _seconds = int64_t(getHour()) * 3600LL + int64_t(getMinute()) * 60LL + int64_t(second);
}

bool Time::operator>(const Time & t2) const noexcept
{
    return toSeconds() > t2.toSeconds();
}

bool Time::operator<(const Time & t2) const noexcept
{
    return toSeconds() < t2.toSeconds();
}

bool Time::operator=(const Time & t2) const noexcept
{
    return toSeconds() == t2.toSeconds();
}

Time Time::difference(const Time & t2) const
{   
    if (t2 > *this)
        return Time(t2.toSeconds() - toSeconds());
    else
        return Time(toSeconds() - t2.toSeconds());
}

Time Time::operator-(const Time & t2) const
{
    return difference(t2);
}

Time Time::operator+(const Time & t2) const
{
    return Time(toSeconds() + t2.toSeconds());
}