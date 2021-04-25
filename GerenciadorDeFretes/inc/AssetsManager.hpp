#ifndef _ASSETSMANAGER_HPP_
#define _ASSETSMANAGER_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>

class AssetsManager
{
public:
    static void setVerboseMode();

    static AssetsManager * getInstance();
    static void shutDown();

    SDL_Texture * getTexture(const std::string & img_name);
    SDL_Texture * getTextTexture(const std::string & font_name, uint8_t font_size, const std::string & text, SDL_Color color = {0,0,0,0});
    TTF_Font * getFont(const std::string & font_name, uint8_t font_size);

private:
    AssetsManager();
    ~AssetsManager();

    static AssetsManager * _instance;

    std::map<std::string, SDL_Texture *> _textures;
    std::map<std::string, TTF_Font *> _fonts;

    static bool VERBOSE;
    static const std::string VERBOSE_MSG;
};

#endif 