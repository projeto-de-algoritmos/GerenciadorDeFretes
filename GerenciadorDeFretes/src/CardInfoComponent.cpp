#include "CardInfoComponent.hpp"
#include "Assets.hpp"

#include <stdexcept>

static void EmptyCallBack(void *)
{

}

CardInfoComponent * CardInfoComponent::newCardInfoComponent(uint16_t width, uint16_t height, const std::string & image_name)
{
    return new CardInfoComponent(width, height, image_name);
}

void CardInfoComponent::pushText(const std::string & text)
{
    DynamicText * dt = DynamicText::newDynamicText(text, Assets::DYNAMICTEXT_FONT_NAME, 16, Assets::DARK_GREEN);
    
    if (_texts.empty()) {
        dt->setParent(this);
        dt->setRelativeX(_image->getWidth() + 15);
        dt->setRelativeY(10);
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

void CardInfoComponent::setCallBackClickReaction(std::function<void(void *)> call_back)
{
    _call_back = call_back;
}

CardInfoComponent::CardInfoComponent(uint16_t width, uint16_t height, const std::string & image_name):
InteractiveComponent(width, height),
_call_back(EmptyCallBack)
{
    VisualComponent::setInvisibility(false);
    VisualComponent::setColor(Assets::SUPER_LIGHT_GREEN);
    InteractiveComponent::tie();
    _image = SolidImage::newSolidImage(image_name, width / 3 - 10, height - 10);
    _image->setParent(this);
    _image->setRelativeX(5);
    _image->setRelativeY(5);
}

CardInfoComponent::~CardInfoComponent()
{
    _call_back(this);
}

void CardInfoComponent::reactToClick(const SDL_Point & cursor_coordinates)
{
    
}

void CardInfoComponent::reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    VisualComponent::setColor(Assets::LIGHT_GREEN);
}

void CardInfoComponent::reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    VisualComponent::setColor(Assets::SUPER_LIGHT_GREEN);
}
