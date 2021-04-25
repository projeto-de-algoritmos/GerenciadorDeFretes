#include "Graphics.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>
#include <iostream>
#include <string> 

Graphics * Graphics::_instance = NULL;
bool Graphics::_started_up = false;

void Graphics::startUp(const char * window_title, uint16_t window_width, uint16_t window_height, const char * icon_path)
{
    if (_started_up)
        return;

    _started_up = true;
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
        throw_sdl_exception("Unable to initialize SDL video subsystem.");

    int img_flags = (IMG_INIT_JPG | IMG_INIT_PNG);
    if (IMG_Init(img_flags) != img_flags)
        throw_img_exception("Unable to initialize PNG or JPG image system");

    if (TTF_Init() == -1)
        throw_ttf_exception("Unable to initialize TTF system");

    _instance = new Graphics(window_title, window_width, window_height, icon_path);
}

void Graphics::shutDown()
{
    _started_up = false;
    delete _instance;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

Graphics * Graphics::getInstance()
{
    startUp();
    return _instance;
}

void Graphics::clearScreen()
{
    setDrawColor(0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);
}

void Graphics::updateScreen()
{
    SDL_RenderPresent(_renderer);
}

void Graphics::setDrawColor(uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetRenderDrawColor(_renderer, r, g, b, 0xFF);
}

void Graphics::drawRectangle(const SDL_Rect * rectangle)
{
    SDL_RenderFillRect(_renderer, rectangle);
}

void Graphics::drawRectangle(SDL_Rect rectangle)
{
    drawRectangle(&rectangle);
}

void Graphics::drawRectangle(const SDL_Rect * rectangle, SDL_Color color)
{
    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);
    setDrawColor(color.r, color.g, color.b);
    drawRectangle(rectangle);
    setDrawColor(r, g, b);
}

void Graphics::drawRectangle(SDL_Rect rectangle, SDL_Color color)
{
    drawRectangle(&rectangle, color);
}

void Graphics::hideCursor() const
{
    SDL_ShowCursor(SDL_DISABLE);
}

void Graphics::showCursor() const
{
    SDL_ShowCursor(SDL_ENABLE);
}

void Graphics::maximizeWindow()
{
    SDL_MaximizeWindow(_window);
}

void Graphics::minimizeWindow()
{
    SDL_MinimizeWindow(_window);
}

void Graphics::setFullScreenMode()
{
    if (SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN) != 0)
        throw_sdl_exception("Unable to set full screen mode");
}

void Graphics::setWindowedMode()
{
    if (SDL_SetWindowFullscreen(_window, 0) != 0)
        throw_sdl_exception("Unable to set windowed mode");
}

uint16_t Graphics::getWindowWidth() const
{
    int _w, _h;
    SDL_GetWindowSize(_window, &_w, &_h);
    return uint16_t(_w);
}

uint16_t Graphics::getWindowHeight() const
{
    int _w, _h;
    SDL_GetWindowSize(_window, &_w, &_h);
    return uint16_t(_h);
}

TTF_Font * Graphics::loadFont(const std::string & font_path, uint8_t font_size) const
{
    TTF_Font * font = TTF_OpenFont(font_path.c_str(), font_size);
    if (font == NULL) {
        std::string msg = "Unable to load font " +  font_path;
        throw_ttf_exception(msg.c_str());
    }
    return font;
}

void Graphics::unloadFont(TTF_Font * font) const
{
    TTF_CloseFont(font);
}

SDL_Texture * Graphics::loadTexture(const char * img_path)
{
    SDL_Surface * temp_surface = loadImage(img_path);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(_renderer, loadImage(img_path));
    SDL_FreeSurface(temp_surface);

    if (texture == NULL) {
        throw_sdl_exception("Unable to create texture from surface.");
    }
    return texture;
}

SDL_Texture * Graphics::loadTexture(const std::string & img_path)
{
    return loadTexture(img_path.c_str());
}

SDL_Texture * Graphics::createTextTexture(TTF_Font * font, const std::string & text, SDL_Color color)
{

    SDL_Surface * temp_surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (temp_surface == NULL) {
        std::string msg = "Unable to make solid text render for text \"" + text + "\"";
        throw_ttf_exception(msg.c_str());
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(_renderer, temp_surface);
    if (texture == NULL) {
        std::string msg = "Unable to create text texture to text \"" + text + "\"";
        throw_sdl_exception(msg.c_str());
    }

    SDL_FreeSurface(temp_surface);
    temp_surface = nullptr;

    return texture;
}

void Graphics::drawTexture(SDL_Texture * texture, SDL_Rect * drawing_area)
{
    if (SDL_RenderCopy(_renderer, texture, NULL, drawing_area) == -1) {
        throw_sdl_exception("Unable to draw a texture");
    }
}

void Graphics::drawTexture(SDL_Texture * texture, SDL_Rect drawing_area)
{
    drawTexture(texture, &drawing_area);
}

void Graphics::drawTexture(SDL_Texture * texture, SDL_Rect * drawing_area, double rotation_angle)
{
    if (SDL_RenderCopyEx(_renderer, texture, NULL, drawing_area, rotation_angle, NULL, SDL_FLIP_NONE) == -1)
        throw_sdl_exception("Unable to draw a texture with rotation");
}

void Graphics::drawTexture(SDL_Texture * texture, SDL_Rect drawing_area, double rotation_angle)
{
    drawTexture(texture, &drawing_area, rotation_angle);
}

void Graphics::unloadTexture(SDL_Texture * texture) const
{
    SDL_DestroyTexture(texture);
}

// // // // // // // // // // // // // // // // // // //
//
// INTERNAL FUNCTIONS
//
//

SDL_Surface * Graphics::loadImage(const char * img_path) const
{
    SDL_Surface * image = IMG_Load(img_path);
    if (image == NULL) {
        std::string msg = "Unable to load the image " + std::string(img_path);
        throw_img_exception(msg.c_str());
    }
    return image;
}

void Graphics::throw_sdl_exception(const char * msg)
{
    std::cerr << msg << " Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("Graphics Exception");
}

void Graphics::throw_img_exception(const char * msg)
{
    std::cerr << msg << " Error: " << IMG_GetError() << std::endl;
    throw std::runtime_error("Graphics Exception");
}

void Graphics::throw_ttf_exception(const char * msg)
{
    std::cerr << msg << "Error: " << TTF_GetError() << std::endl;
    throw std::runtime_error("TTF Exception");
}

Graphics::Graphics(const char * window_title, uint16_t window_width, uint16_t window_height, const char * icon_path)
{
    _window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (_window == NULL)
        throw_sdl_exception("Unable to create SDL_window.");

    if (icon_path != NULL) {
        SDL_Surface * icon = loadImage(icon_path);
        SDL_SetWindowIcon(_window, icon);
        SDL_FreeSurface(icon);
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
        throw_sdl_exception("Unable to create SDL_renderer.");

    setDrawColor(0xFF, 0xFF, 0xFF);
    clearScreen();
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}
