#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <iostream>

AssetsManager * AssetsManager::_instance = nullptr;
bool AssetsManager::VERBOSE = false;
const std::string AssetsManager::VERBOSE_MSG = "\033[0;33m(VERBOSE) AssetsManager:\033[0m\t";

void AssetsManager::setVerboseMode()
{
    VERBOSE = true;
}

AssetsManager * AssetsManager::getInstance()
{
    if (_instance == nullptr)
        _instance = new AssetsManager();
    return _instance;
}

void AssetsManager::shutDown()
{
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

SDL_Texture * AssetsManager::getTexture(const std::string & img_name)
{
    std::string texture_key = img_name;

    if (_textures.count(texture_key) < 1) {
        Graphics * graphics = Graphics::getInstance();
        std::string img_path = "assets/" + img_name;   
        _textures[texture_key] = graphics->loadTexture(img_path);
        
        if (VERBOSE) std::cout << VERBOSE_MSG + "Creating texture with key: " << texture_key << std::endl;
    }

    return _textures[texture_key];
}

SDL_Texture * AssetsManager::getTextTexture(const std::string & font_name, uint8_t font_size, const std::string & text, SDL_Color color)
{
    std::string text_texture_key = font_name + std::to_string(font_size) + text;
    text_texture_key.append(std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b));
    

    if (_textures.count(text_texture_key) < 1) {
        TTF_Font * font = getFont(font_name, font_size);
        Graphics * graphics = Graphics::getInstance();
        _textures[text_texture_key] = graphics->createTextTexture(font, text, color);
        
        if (VERBOSE) std::cout << VERBOSE_MSG + "Creating Text Texture with key: " << text_texture_key << std::endl;
    }

    return _textures[text_texture_key];
}

TTF_Font * AssetsManager::getFont(const std::string & font_name, uint8_t font_size)
{
    std::string font_key = font_name + std::to_string(font_size);

    if (_fonts.count(font_key) < 1) {
        Graphics * graphics = Graphics::getInstance();
        _fonts[font_key] = graphics->loadFont("assets/" + font_name, font_size);
        
        if (VERBOSE) std::cout << VERBOSE_MSG + "Creating Font with key: " << font_key << std::endl; 
    }

    return _fonts[font_key];
}

AssetsManager::AssetsManager()
{

}

AssetsManager::~AssetsManager()
{
    Graphics * graphics = Graphics::getInstance();
    for (auto texture : _textures) {
        graphics->unloadTexture(texture.second);
        
        if (VERBOSE) std::cout << VERBOSE_MSG + "Destroying texture with key: " << texture.first << std::endl;
    }
    for (auto font : _fonts) {
        graphics->unloadFont(font.second);
        
        if (VERBOSE) std::cout << VERBOSE_MSG + "Destroying font with key: " << font.first << std::endl;
    }
}