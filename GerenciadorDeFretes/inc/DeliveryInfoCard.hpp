#ifndef _DELIVERY_INFO_CARD_HPP_
#define _DELIVERY_INFO_CARD_HPP_

#include "CardInfoComponent.hpp"
#include "Delivery.hpp"

class DeliveryInfoCard : public CardInfoComponent
{
public:
    static DeliveryInfoCard * newDeliveryInfoCard(Delivery * delivery, uint16_t width, uint16_t height);

    Delivery * getDelivery() noexcept;
    void setDelivery(Delivery * delivery);

    void updateDeliveryCard();

private:
    DeliveryInfoCard(Delivery * delivery, uint16_t width, uint16_t height);
    virtual ~DeliveryInfoCard();

    Delivery * _delivery;

protected:

};

#endif