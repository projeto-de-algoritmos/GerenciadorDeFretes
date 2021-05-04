#include "DeliveryInfoCard.hpp"

#include <string>

DeliveryInfoCard * DeliveryInfoCard::newDeliveryInfoCard(Delivery * delivery, uint16_t width, uint16_t height)
{
    return new DeliveryInfoCard(delivery, width, height);
}

Delivery * DeliveryInfoCard::getDelivery() noexcept
{
    return _delivery;
}

void DeliveryInfoCard::setDelivery(Delivery * delivery)
{
    _delivery = delivery;
    updateDeliveryCard();
}

void DeliveryInfoCard::updateDeliveryCard()
{
    CardInfoComponent::updateText(0, _delivery->getName());
    CardInfoComponent::updateText(1, "Inicio: " + _delivery->getStartTime().toString());
    CardInfoComponent::updateText(2, "Termino: " + _delivery->getEndTime().toString());
    CardInfoComponent::updateText(3, "Lucro: " + std::to_string(int32_t(_delivery->getProfit())) + ".00");
}

DeliveryInfoCard::DeliveryInfoCard(Delivery * delivery, uint16_t width, uint16_t height):
CardInfoComponent(width, height, Assets::DELIVERY_PICTURE_NAME),
_delivery(delivery)
{
    CardInfoComponent::pushText(_delivery->getName());
    CardInfoComponent::pushText("Inicio: " + _delivery->getStartTime().toString());
    CardInfoComponent::pushText("Termino: " + _delivery->getEndTime().toString());
    CardInfoComponent::pushText("Lucro: " + std::to_string(int32_t(_delivery->getProfit())) + ".00");
}

DeliveryInfoCard::~DeliveryInfoCard()
{

}
