#include "DriverInfoCard.hpp"
#include "Assets.hpp"

#include <string>

DriverInfoCard * DriverInfoCard::newDriverInfoCard(Driver * driver, uint16_t width, uint16_t height)
{
    return new DriverInfoCard(driver, width, height);
}

Driver * DriverInfoCard::getDriver() noexcept
{
    return _driver;
}

void DriverInfoCard::setDriver(Driver * driver)
{
    _driver = driver;
}

void DriverInfoCard::updateDriverCard()
{
    CardInfoComponent::updateText(0, _driver->getDriverName());
    CardInfoComponent::updateText(1, std::to_string(_driver->getDriverAge()) + " anos");
    CardInfoComponent::updateText(2, "Dirige um(a) " + _driver->getDriverVehicleName());
}

DriverInfoCard::DriverInfoCard(Driver * driver, uint16_t width, uint16_t height):
CardInfoComponent(width, height, Assets::DRIVER_PICTURE_NAME),
_driver(driver)
{
    CardInfoComponent::pushText(_driver->getDriverName());
    CardInfoComponent::pushText(std::to_string(_driver->getDriverAge()) + " anos");
    CardInfoComponent::pushText("Dirige um(a) " + _driver->getDriverVehicleName());
}

DriverInfoCard::~DriverInfoCard()
{
    
}

void DriverInfoCard::reactToClick(const SDL_Point & cursor_coordinates)
{
    _call_back(getDriver());
}