#ifndef _DRIVER_INFO_CARD_HPP_
#define _DRIVER_INFO_CARD_HPP_

#include "CardInfoComponent.hpp"
#include "Driver.hpp"

class DriverInfoCard : public CardInfoComponent
{
public:
    static DriverInfoCard * newDriverInfoCard(Driver * driver, uint16_t width, uint16_t height);

    Driver * getDriver() noexcept;
    void setDriver(Driver * driver);

    void updateDriverCard();

private:
    DriverInfoCard(Driver * driver, uint16_t width, uint16_t height);
    virtual ~DriverInfoCard();

    Driver * _driver;

protected:
    //The reaction when the component takes a mouse click
    virtual void reactToClick(const SDL_Point & cursor_coordinates) override;
};

#endif