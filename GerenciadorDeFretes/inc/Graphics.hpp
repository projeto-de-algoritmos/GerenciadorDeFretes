#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Assets.hpp"

#include <stdint.h>
#include <string>

class Graphics
{
public:
    static void startUp(const char * window_title = Assets::WINDOW_TITLE.c_str(),
                        uint16_t window_width = Assets::WINDOW_WIDTH,
                        uint16_t window_height = Assets::WINDOW_HEIGHT,
                        const char * icon_path = Assets::WINDOW_ICON_IMAGE_NAME.c_str());
    static void shutDown();
    static Graphics * getInstance();

    void clearScreen();
    void updateScreen();
    void setDrawColor(uint8_t r, uint8_t g, uint8_t b);

    void drawRectangle(const SDL_Rect * rectangle);
    void drawRectangle(SDL_Rect rectangle);
    void drawRectangle(const SDL_Rect * rectangle, SDL_Color color);
    void drawRectangle(SDL_Rect rectangle, SDL_Color color);
    
    void hideCursor() const;
    void showCursor() const;
    void maximizeWindow();
    void minimizeWindow();
    void setFullScreenMode();
    void setWindowedMode();

    uint16_t getWindowWidth() const;
    uint16_t getWindowHeight() const;

    TTF_Font * loadFont(const std::string & font_path, uint8_t font_size) const;
    void unloadFont(TTF_Font * font) const;

    SDL_Texture * loadTexture(const char * img_path);
    SDL_Texture * loadTexture(const std::string & img_path);
    SDL_Texture * createTextTexture(TTF_Font * font, const std::string & text, SDL_Color color = {0,0,0,0});
    void drawTexture(SDL_Texture * texture, SDL_Rect * drawing_area);
    void drawTexture(SDL_Texture * texture, SDL_Rect drawing_area);
    void drawTexture(SDL_Texture * texture, SDL_Rect * drawing_area, double rotation_angle);
    void drawTexture(SDL_Texture * texture, SDL_Rect drawing_area, double rotation_angle);
    void unloadTexture(SDL_Texture * texture) const;

private:
    static Graphics * _instance;
    static bool _started_up;

    SDL_Surface * loadImage(const char * img_path) const;

    static void throw_sdl_exception(const char * msg);
    static void throw_img_exception(const char * msg);
    static void throw_ttf_exception(const char * msg);

    Graphics(const char * window_title, uint16_t window_width, uint16_t window_height, const char * icon_path);
    ~Graphics();
    SDL_Window * _window;
    SDL_Renderer * _renderer;
};

#endif