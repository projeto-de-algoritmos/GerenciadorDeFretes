#include "TextField.hpp"
#include "SolidImage.hpp"
#include "DynamicText.hpp"
#include <iostream>

TextField * TextField::newTextField(const uint16_t width,
                                    const uint16_t height,
                                    const std::string & normal_background_name,
                                    const std::string & highlight_background_name,
                                    const std::string & focused_background,
                                    const uint16_t max_chars)
{
    TextField * tf = new TextField(width, height);
    tf->_normal_background = SolidImage::newSolidImage(normal_background_name, width, height);
    tf->_normal_background->setParent(tf);
    tf->_normal_background->setRelativeX(0);
    tf->_normal_background->setRelativeY(0);
    tf->_normal_background->show();

    tf->_highlight_background = SolidImage::newSolidImage(highlight_background_name, width, height);
    tf->_highlight_background->setParent(tf);
    tf->_highlight_background->setRelativeX(0);
    tf->_highlight_background->setRelativeY(0);
    tf->_highlight_background->hide();

    tf->_focused_background = SolidImage::newSolidImage(focused_background, width, height);
    tf->_focused_background->setParent(tf);
    tf->_focused_background->setRelativeX(0);
    tf->_focused_background->setRelativeY(0);
    tf->_focused_background->hide();

    tf->_content = DynamicText::newDynamicText("Type here...");
    tf->_content->setParent(tf);
    tf->_content->setRelativeX(8);
    tf->_content->setRelativeY(5);
    
    tf->setAlphaNumericMode();
    tf->tie();
    tf->_max_chars = max_chars;

    return tf;
}

std::string TextField::getContent() const noexcept
{
    return _content->getText();
}

bool TextField::isAlphaOnlyMode() const noexcept
{
    return _mode_flag == 1;
}

void TextField::setAlphaOnlyMode() noexcept
{
    _content->setText("Type here");
    _mode_flag = 1;
}

bool TextField::isNumericOnlyMode() const noexcept
{
    return _mode_flag == 2;
}

void TextField::setNumericOnlyMode() noexcept
{
    _content->setText("0.0");
    _mode_flag = 2;
}

bool TextField::isAlphaNumericMode() const noexcept
{
    return _mode_flag == 3;
}

void TextField::setAlphaNumericMode() noexcept
{
    _mode_flag = 3;
}

double TextField::getNumericValue() const noexcept
{
    if (!isNumericOnlyMode())
        return 0.0;

    auto str = _content->getText();
    int dotpos = -1;
    for (int i = 0; i < (int32_t) str.size(); i++) {
        if (str[i] == '.') {
            dotpos = i;
            break;
        }
    }
    if (dotpos == (int32_t) str.size() - 1 || str.size() == 0)
        str.push_back('0');

    return std::stod(str);
}

bool TextField::isAlpha(int32_t c)
{
    return (c >= int32_t('a') && c <= int32_t('z')) || (c >= int32_t('A') && c <= int32_t('Z') || c == ' ');
}

bool TextField::isNumeric(int32_t c)
{
    return c >= int32_t('0') && c <= int32_t('9');
}

bool TextField::isBackspace(int32_t c)
{
    return c == SDLK_BACKSPACE;
}

bool TextField::validateNumber(int32_t c)
{
    if (!isNumericOnlyMode())
        return false;

    else if (c != (int32_t) '.' && c != (int32_t) ',' && c != '-' && !isNumeric(c))
        return false;

    else if (c == '-' && _content->getText().size() > 0)
        return false;

    else if (c == '.' || c == ',') {
        std::string tmp = _content->getText();
        for (auto e : tmp) {
            if (e == '.')
                return false;
        }
    }

    return true;
}

bool TextField::validateAlpha(int32_t c)
{
    if (!isAlphaOnlyMode() || !isAlpha(c))
        return false;
    return true;
}

bool TextField::validateText(int32_t c)
{
    return (isAlpha(c) || isNumeric(c) || c == int32_t(' ')) && isAlphaNumericMode();
}

TextField::TextField(uint16_t width, uint16_t height):
InteractiveComponent(width, height)
{

}

TextField::TextField(TextField & tf):
InteractiveComponent(0,0),
_mode_flag(tf._mode_flag),
_normal_background(tf._normal_background),
_highlight_background(tf._highlight_background),
_focused_background(tf._focused_background),
_content(tf._content)
{

}

TextField::~TextField()
{

}

void TextField::reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    if (isFocused())
        return;
    
    _normal_background->hide();
    _highlight_background->show();
    _focused_background->hide();
}

void TextField::reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    if (isFocused())
        return;

    _normal_background->show();
    _highlight_background->hide();
    _focused_background->hide();
}

void TextField::reactToFocusGaining()
{
    _normal_background->hide();
    _highlight_background->hide();
    _focused_background->show();
}

void TextField::reactToFocusLosing()
{
    _normal_background->show();
    _highlight_background->hide();
    _focused_background->hide();
}

void TextField::reactToKeyPressing(int32_t sdl_keysym)
{
    if (validateText(sdl_keysym) || validateAlpha(sdl_keysym) || validateNumber(sdl_keysym)) {
        auto tmp = _content->getText();
        if ((uint16_t) tmp.size() + 1 < _max_chars)
        _content->setText(tmp + std::string(1, (char) sdl_keysym));
    }
    else if (isBackspace(sdl_keysym)) {
        auto tmp = _content->getText();
        if (tmp.size() > 0)
            tmp.pop_back();
        _content->setText(tmp);
    }
}
