#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include "Assets.hpp"

#include <SDL2/SDL.h>

#include <functional>
#include <string>

class Button : public InteractiveComponent
{
public:
    static Button * newButton(  const std::string & button_text,
                                const std::string & background_image_name = Assets::BUTTON_BACKGROUND_IMAGE_NAME,
                                const std::string & font_name = Assets::BUTTON_FONT_NAME,
                                const SDL_Color & font_color = Assets::BUTTON_FONT_COLOR,
                                uint8_t font_size = Assets::BUTTON_FONT_SIZE,
                                uint16_t width = Assets::BUTTON_WIDTH,
                                uint16_t height = Assets::BUTTON_HEIGHT );

    void setClickReaction(std::function<void()> call_back_function);

    void setWidth(uint16_t width);
    void setHeight(uint16_t height);

    void hide();
    void show();

private:
    Button();
    Button(const Button & cpy);

    std::function<void()> _call_back_function;
    SolidImage * _highlight;
    SolidImage * _shade;
    SolidText * _text;

protected:
    Button(uint16_t width, uint16_t height, SDL_Texture * texture = nullptr);
    virtual ~Button();

    virtual void reactToPressing(const SDL_Point & cursor_coordinates) override;
    virtual void reactToReleasing(const SDL_Point & cursor_coordinates) override;
    virtual void reactToClick(const SDL_Point & cursor_coordinates) override;
    virtual void reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates) override;
    virtual void reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates) override;
}; 

#endif