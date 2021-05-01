#include "Driver.hpp"

Driver::Driver(const std::string & name,
               const uint16_t age,
               const std::string vehicle_name):
_name(name),
_age(age),
_vehicle_name(vehicle_name)
{

}

Driver::~Driver()
{

}

std::string Driver::getDriverName() const noexcept
{
    return _name;
}

void Driver::setDriverName(const std::string & new_name) noexcept
{
    _name = new_name;
}

uint16_t Driver::getDriverAge() const noexcept
{
    return _age;
}

void Driver::setDriverAge(const uint16_t new_age) noexcept
{
    _age = new_age;
}

std::string Driver::getDriverVehicleName() const noexcept
{
    return _vehicle_name;
}

void Driver::setDriverVehicleName(const std::string & new_vehicle_name) noexcept
{
    _vehicle_name = new_vehicle_name;
}