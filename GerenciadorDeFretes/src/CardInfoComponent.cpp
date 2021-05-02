#include "CardInfoComponent.hpp"

#include <stdexcept>

CardInfoComponent * CardInfoComponent::newCardInfoComponent(uint16_t width, uint16_t height, const std::string & image_name)
{
    return new CardInfoComponent(width, height, image_name);
}

void CardInfoComponent::pushText(const std::string & text)
{
    DynamicText * dt = DynamicText::newDynamicText(text);
    
    if (_texts.empty()) {
        dt->setParent(this);
        dt->setRelativeX(_image->getWidth() + 5);
        dt->setRelativeY(0);
    } else {
        dt->setParent(_texts.back());
        dt->setRelativeX(0);
        dt->setRelativeY(_texts.back()->getHeight() + 3);
    }
    _texts.push_back(dt);
}

void CardInfoComponent::updateText(int32_t index, const std::string & text)
{
    if (index >= int32_t(_texts.size()))
        throw std::runtime_error("Attempt to update text inside CardInfoComponent out of range");

    _texts[index]->setText(text);
}

void CardInfoComponent::setCallBackClickReaction(std::function<void()> call_back)
{
    _call_back = call_back;
}

CardInfoComponent::CardInfoComponent(uint16_t width, uint16_t height, const std::string & image_name):
InteractiveComponent(width, height),
_call_back(EmptyCallBack)
{
    VisualComponent::setInvisibility(false);
    VisualComponent::setColor({255, 255, 255, 255});
    InteractiveComponent::tie();
    _image = SolidImage::newSolidImage(image_name, width / 3, height);
    _image->setParent(this);
    _image->setRelativeX(0);
    _image->setRelativeY(0);
}

static void EmptyCallBack()
{

}