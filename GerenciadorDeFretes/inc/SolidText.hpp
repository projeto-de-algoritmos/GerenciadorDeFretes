#ifndef _SOLIDTEXT_HPP_
#define _SOLIDTEXT_HPP_

#include "Assets.hpp"
#include "VisualComponent.hpp"

#include <string>
#include <cstdint>

class SolidText : public VisualComponent
{
public:
    static SolidText * newSolidText(const std::string & text,
                                    const std::string & font_name = Assets::SOLIDTEXT_FONT_NAME,
                                    uint8_t font_size = Assets::SOLIDTEXT_FONT_SIZE,
                                    SDL_Color color = Assets::SOLIDTEXT_FONT_COLOR);

private:
    SolidText(uint16_t width = 0, uint16_t height = 0, SDL_Texture * texture = nullptr);
    virtual ~SolidText();
};

#endif