#ifndef _CHECKBOX_HPP_
#define _CHECKBOX_HPP_

#include "InteractiveComponent.hpp"
#include "VisualComponent.hpp"
#include "SolidText.hpp"
#include "SolidImage.hpp"

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <functional>

class Checkbox : public InteractiveComponent
{
public:
    static Checkbox * newCheckbox( const std::string & label,
                            const std::string & checked_texture = Assets::CHECKBOX_CHECKED_TEXTURE,
                            const std::string & checked_highlight = Assets::CHECKBOX_CHECKED_HIGHLIGHT,
                            const std::string & unchecked_texture = Assets::CHECKBOX_UNCHECKED_TEXTURE,
                            const std::string & unchecked_hightlight = Assets::CHECKBOX_UNCHECKED_HIGHLIGHT,
                            uint16_t width_height = Assets::CHECKBOX_WIDTH_HEIGHT,
                            const std::string & font_name = Assets::CHECKBOX_FONT_NAME,
                            uint16_t font_size = Assets::CHECKBOX_FONT_SIZE,
                            const SDL_Color & font_color = Assets::CHECKBOX_FONT_COLOR,
                            const std::function<void(bool)> check_reaction = Assets::CHECKBOX_EMPTY_REACTION);

    void setCheckReaction(std::function<void(bool)> check_reaction);

    bool isChecked() const noexcept;
    void check() noexcept;
    void uncheck() noexcept;

    void hide();
    void show();

private:
    Checkbox(uint16_t width_height = 0);
    Checkbox(Checkbox &);
    virtual ~Checkbox();

    std::function<void(bool)> _check_reaction;

    bool _is_checked;

    SolidImage * _checked_texture;
    SolidImage * _checked_highlight;
    SolidImage * _unchecked_texture;
    SolidImage * _unchecked_highlight;
    SolidText * _label;

protected:

    //The reaction when the component takes a mouse click
    virtual void reactToClick(const SDL_Point & cursor_coordinates) override;

    // The reaction when the mouse cursor is overlapping the component (with no clicks or pressings)
    virtual void reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates) override;

    // The reaction when the mouse cursor stops overlapping the component (with no clicks or pressings)
    virtual void reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates) override;

};

#endif