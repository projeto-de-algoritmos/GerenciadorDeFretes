#ifndef _DELIVERY_HPP_
#define _DELIVERY_HPP_

#include "Time.hpp"

#include <string>
#include <cstdint>

class Delivery
{
public:
    Delivery(const std::string & name,
             const Time & start,
             const Time & end,
             const double profit);

    ~Delivery();

    std::string getName() const noexcept;
    void setName(const std::string & name) noexcept;

    Time getStartTime() const noexcept;
    void setStartTime(const Time & t);

    Time getEndTime() const noexcept;
    void setEndTime(const Time & t);

    double getProfit() const noexcept;
    // Returns profit * 100 as Interger
    int32_t getShiftedIntergerProfit() const noexcept;
    void setProfit(double profit) noexcept;
private:
    std::string _name;
    Time _start;
    Time _end;
    double _profit;

protected:

};

#endif