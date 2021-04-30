#ifndef _TEXT_FIELD_HPP_
#define _TEXT_FIELD_HPP_

#include "InteractiveComponent.hpp"
#include "DynamicText.hpp"
#include "SolidImage.hpp"
#include "Assets.hpp"

#include <cstdint>
#include <string>

class TextField : public InteractiveComponent
{
public:
    static TextField * newTextField(const uint16_t width = Assets::TEXTFIELD_WIDTH,
                                    const uint16_t height = Assets::TEXTFIELD_HEIGHT,
                                    const std::string & normal_background_name = Assets::TEXTFIELD_NORMAL_BACKGROUND,
                                    const std::string & highlight_background_name = Assets::TEXTFIELD_HIGHLIGHT_BACKGROUND,
                                    const std::string & focused_background_name = Assets::TEXTFIELD_FOCUSED_BACKGROUND,
                                    const uint16_t max_chars = Assets::TEXTFIELD_MAXCHARS);

    std::string getContent() const noexcept;

    bool isAlphaOnlyMode() const noexcept;
    void setAlphaOnlyMode() noexcept;

    bool isNumericOnlyMode() const noexcept;
    void setNumericOnlyMode() noexcept;

    bool isAlphaNumericMode() const noexcept;
    void setAlphaNumericMode() noexcept;

    double getNumericValue() const noexcept;

private:
    bool isAlpha(int32_t c);
    bool isNumeric(int32_t c);
    bool isBackspace(int32_t c);

    bool validateNumber(int32_t c);
    bool validateAlpha(int32_t c);
    bool validateText(int32_t c);

    TextField(uint16_t width = 0, uint16_t height = 0);
    TextField(TextField &);
    ~TextField();

    uint16_t _max_chars;
    int32_t _mode_flag;

    SolidImage * _normal_background;
    SolidImage * _highlight_background;
    SolidImage * _focused_background;
    DynamicText * _content;

protected:
    // The reaction when the mouse cursor is overlapping the component (with no clicks or pressings)
    virtual void reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates) override;

    // The reaction when the mouse cursor stops overlapping the component (with no clicks or pressings)
    virtual void reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates) override;

    // The reaction when this component gain focus
    virtual void reactToFocusGaining() override;

    // The reaction when this component loses focus
    virtual void reactToFocusLosing() override;

    // The reaction when a key from keyboard is pressed
    virtual void reactToKeyPressing(int32_t sdl_keysym) override;

};

#endif