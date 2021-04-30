#ifndef _DYNAMIC_TEXT_HPP_
#define _DYNAMIC_TEXT_HPP_

#include "VisualComponent.hpp"
#include "SolidText.hpp"
#include "Assets.hpp"

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class DynamicText : public VisualComponent
{
public:
    static DynamicText * newDynamicText(const std::string & text,
                                        const std::string & font_name = Assets::DYNAMICTEXT_FONT_NAME,
                                        uint16_t font_size = Assets::DYNAMICTEXT_FONT_SIZE,
                                        const SDL_Color & font_color = Assets::DYNAMICTEXT_FONT_COLOR);

    void setText(const std::string & text);
    std::string getText() const noexcept;

    uint16_t getWidth() const noexcept;
    uint16_t getHeight() const noexcept;

    void hide();
    void show();

private:
    DynamicText(const std::string & font_name = "",
                uint16_t font_size = 0,
                const SDL_Color & font_color = {0xff, 0xff, 0xff, 0xff});

    DynamicText(DynamicText &);
    virtual ~DynamicText();

    std::string _text;
    SDL_Color _font_color;
    uint16_t _font_size;
    std::string _font_name;
    std::vector<SolidText *> _chars;

protected:

};

#endif