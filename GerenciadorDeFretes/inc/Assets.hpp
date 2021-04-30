#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <functional>

// Every project asset/property should be referenced here

namespace Assets
{
    static void checkboxEmptyReaction(bool a)
    {
        a = !a;
    }
    // Main menu assets
    const std::string   MAIN_MENU_BACKGROUND = "main_menu_background.png";

    // Button assets
    const std::string   BUTTON_FONT_NAME = "arial.ttf",
                        BUTTON_BACKGROUND_IMAGE_NAME = "button_background.png",
                        BUTTON_HIGHLIGHT_NAME = "button_highlight.png",
                        BUTTON_SHADE_NAME = "button_shade.png";
    const SDL_Color     BUTTON_FONT_COLOR = {0xff, 0xff, 0xff, 0xff};
    const uint16_t      BUTTON_FONT_SIZE = 14,
                        BUTTON_WIDTH = 120,
                        BUTTON_HEIGHT = 42;

    // Window assets
    const std::string   WINDOW_TITLE = "Gerenciador de Fretes",
                        WINDOW_ICON_IMAGE_NAME = "assets/delivery_logo.png";
    const uint16_t      WINDOW_WIDTH = 720,
                        WINDOW_HEIGHT = 480;

    // Timer assets
    const double_t      _60_FPS_FRAMETIME = 1.0 / 60.0,
                        _30_FPS_FRAMETIME = 1.0 / 30.0;

    // Checkbox assets
    const uint16_t                  CHECKBOX_WIDTH_HEIGHT = 28,
                                    CHECKBOX_FONT_SIZE = 11;
    const std::string               CHECKBOX_CHECKED_TEXTURE = "checkbox_checked_texture.png",
                                    CHECKBOX_CHECKED_HIGHLIGHT = "checkbox_checked_hightlight.png",
                                    CHECKBOX_UNCHECKED_TEXTURE = "checkbox_unchecked_texture.png",
                                    CHECKBOX_UNCHECKED_HIGHLIGHT = "checkbox_unchecked_highlight.png",
                                    CHECKBOX_FONT_NAME = "arial.ttf";
    const SDL_Color                 CHECKBOX_FONT_COLOR = {0x1f, 0x1f, 0x1f, 0xff};
    const std::function<void(bool)> CHECKBOX_EMPTY_REACTION = checkboxEmptyReaction;

    // Dynamic Text Assets
    const std::string   DYNAMICTEXT_FONT_NAME = "arial.ttf";
    const SDL_Color     DYNAMICTEXT_FONT_COLOR = {0x0, 0x0, 0x0, 0xff};
    const uint16_t      DYNAMICTEXT_FONT_SIZE = 13;

    // SolidText Assets
    const std::string   SOLIDTEXT_FONT_NAME = "arial.ttf";
    const uint8_t       SOLIDTEXT_FONT_SIZE = 14;
    const SDL_Color     SOLIDTEXT_FONT_COLOR = {0x1f, 0x1f, 0x1f, 0xff};

    // Text field Assets
    const uint16_t      TEXTFIELD_WIDTH = 200,
                        TEXTFIELD_HEIGHT = 23,
                        TEXTFIELD_MAXCHARS = 22;
    const std::string   TEXTFIELD_NORMAL_BACKGROUND = "normal_textfield.png",
                        TEXTFIELD_HIGHLIGHT_BACKGROUND = "highlight_textfield.png",
                        TEXTFIELD_FOCUSED_BACKGROUND = "focused_textfield.png";
}

#endif