#include "SolidText.hpp"
#include "AssetsManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SolidText * SolidText::newSolidText(const std::string & text,
                                    const std::string & font_name,
                                    uint8_t font_size,
                                    SDL_Color color)
{

    AssetsManager * am = AssetsManager::getInstance();
    int32_t width, height;
    TTF_SizeText(am->getFont(font_name, font_size), text.c_str(), &width, &height);

    return new SolidText(width, height, am->getTextTexture(font_name, font_size, text, color));
}

SolidText::SolidText(uint16_t width, uint16_t height, SDL_Texture * texture):
VisualComponent(width, height, {0xFF, 0xFF, 0xFF, 0xFF}, texture)
{

}

SolidText::~SolidText()
{

}