#include "Button.hpp"
#include "AssetsManager.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include "Assets.hpp"

#include <iostream>

Button * Button::newButton( const std::string & button_text,
                            const std::string & background_image_name,
                            const std::string & font_name,
                            const SDL_Color & font_color,
                            uint8_t font_size,
                            uint16_t width,
                            uint16_t height )
{

    Button * button = new Button(width, height, AssetsManager::getInstance()->getTexture(background_image_name));
    SolidText * text = SolidText::newSolidText(button_text, font_name, font_size, font_color);

    SolidImage * highlight = SolidImage::newSolidImage(Assets::BUTTON_HIGHLIGHT_NAME, width, height);
    highlight->setParent(button);
    highlight->setRelativeX(0);
    highlight->setRelativeY(0);
    highlight->hide();
    button->_highlight = highlight;

    SolidImage * shade = SolidImage::newSolidImage(Assets::BUTTON_SHADE_NAME, width, height);
    shade->setParent(button);
    shade->setRelativeX(0);
    shade->setRelativeY(0);
    shade->hide();
    button->_shade = shade;
    
    text->setParent(button);
    text->setRelativeX((button->getWidth() / 2) - (text->getWidth() / 2));
    text->setRelativeY((button->getHeight() / 2) - (text->getHeight() / 2));
    button->_text = text;

    button->tie();

    return button;
}

void Button::setClickReaction(std::function<void()> call_back_function)
{
    _call_back_function = call_back_function;
}

void Button::setWidth(uint16_t width)
{
    VisualComponent::setWidth(width);
    _shade->setWidth(width);
    _text->setRelativeX((width / 2) - (_text->getWidth() / 2));
}

void Button::setHeight(uint16_t height)
{
    VisualComponent::setHeight(height);
    _shade->setHeight(height);
    _text->setRelativeY((height / 2) - (_text->getHeight() / 2));
}

void Button::hide()
{
    VisualComponent::hide();
    _highlight->hide();
    _shade->hide();
    _text->hide();
}

void Button::show()
{
    VisualComponent::show();
    _highlight->hide();
    _shade->hide();
    _text->show();
}

Button::Button(uint16_t width, uint16_t height, SDL_Texture * texture):
InteractiveComponent(width, height, {0xFF, 0xFF, 0xFF, 0xFF}, texture)
{

}

Button::~Button()
{

}

void Button::reactToPressing(const SDL_Point & cursor_coordinates)
{
    _shade->show();
}

void Button::reactToReleasing(const SDL_Point & cursor_coordinates)
{
    _shade->hide();
}

void Button::reactToClick(const SDL_Point & cursor_coordinates)
{
    _call_back_function();
}

void Button::reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    _highlight->show();
}

void Button::reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    _highlight->hide();
}