#include "Delivery.hpp"
#include <stdexcept>

Delivery::Delivery(const std::string & name,
                   const Time & start,
                   const Time & end,
                   const double profit):
_name(name),
_start(start),
_end(end),
_profit(profit)
{
    if (start > end)
        throw std::runtime_error("Attempt to create a delivery object with invalid start/end time:" + start.toString() + " " + end.toString());
}

Delivery::~Delivery()
{

}

std::string Delivery::getName() const noexcept
{
    return _name;
}

void Delivery::setName(const std::string & name) noexcept
{
    _name = name;
}

Time Delivery::getStartTime() const noexcept
{
    return _start;
}

void Delivery::setStartTime(const Time & t)
{
    if (_end < t)
        throw std::runtime_error("Attempt to set start time later than end time: " + t.toString() + ":" + _end.toString());
    _start = t;
}

Time Delivery::getEndTime() const noexcept
{
    return _end;
}

void Delivery::setEndTime(const Time & t)
{
    if (t < _start)
        throw std::runtime_error("Attempt to set end time earlier than start time: " + _start.toString() + ":" + t.toString());
    _end = t;
}

double Delivery::getProfit() const noexcept
{
    return _profit;
}

int32_t Delivery::getShiftedIntergerProfit() const noexcept
{
    return _profit * 100;
}

void Delivery::setProfit(double profit) noexcept
{
    _profit = profit;
}
