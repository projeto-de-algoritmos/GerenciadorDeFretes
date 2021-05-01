#ifndef _TIME_HPP_
#define _TIME_HPP_

#include <string>
#include <cstdint>

class Time
{
public:
    // hh:mm:ss
    Time(const std::string & str_time);
    Time(const uint16_t hour, const uint16_t minute, const uint16_t second);
    Time(const int64_t seconds);
    ~Time();

    std::string toString() const noexcept;
    int64_t toSeconds() const noexcept;

    uint16_t getHour() const noexcept;
    void setHour(const uint16_t hour) noexcept;

    uint16_t getMinute() const noexcept;
    void setMinute(const uint16_t minute) noexcept;

    uint16_t getSecond() const noexcept;
    void setSecond(const uint16_t second) noexcept;

    bool operator>(const Time & t2) const noexcept;
    bool operator<(const Time & t2) const noexcept;
    bool operator=(const Time & t2) const noexcept;

    // Absolute difference between two times
    Time difference(const Time & t2) const;
    
    Time operator-(const Time & t2) const;

    Time operator+(const Time & t2) const;
private:
    int64_t _seconds = 0;

protected:

};

#endif