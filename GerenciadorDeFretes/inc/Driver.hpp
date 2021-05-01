#ifndef _DRIVER_HPP_
#define _DRIVER_HPP_

#include <string>
#include <cstdint>

class Driver
{
public:
    Driver(const std::string & name,
           const uint16_t age,
           const std::string vehicle_name);

    ~Driver();

    std::string getDriverName() const noexcept;
    void setDriverName(const std::string & new_name) noexcept;

    uint16_t getDriverAge() const noexcept;
    void setDriverAge(const uint16_t new_age) noexcept;

    std::string getDriverVehicleName() const noexcept;
    void setDriverVehicleName(const std::string & new_vehicle_name) noexcept;

private:
    std::string _name;
    uint16_t _age;
    std::string _vehicle_name;

protected:

};

#endif