#include "Checkbox.hpp"
#include "SolidImage.hpp"
#include "AssetsManager.hpp"

Checkbox * Checkbox::newCheckbox(const std::string & label,
                                const std::string & checked_texture,
                                const std::string & checked_highlight,
                                const std::string & unchecked_texture,
                                const std::string & unchecked_hightlight,
                                uint16_t width_height,
                                const std::string & font_name,
                                uint16_t font_size,
                                const SDL_Color & font_color,
                                const std::function<void(bool)> check_reaction)
{
    Checkbox * checkbutton = new Checkbox(width_height);
    checkbutton->_checked_texture = SolidImage::newSolidImage(checked_texture, width_height, width_height);
    checkbutton->_checked_texture->setParent(checkbutton);
    checkbutton->_checked_texture->setRelativeX(0);
    checkbutton->_checked_texture->setRelativeY(0);
    checkbutton->_checked_texture->hide();

    checkbutton->_checked_highlight = SolidImage::newSolidImage(checked_highlight, width_height, width_height);
    checkbutton->_checked_highlight->setParent(checkbutton);
    checkbutton->_checked_highlight->setRelativeX(0);
    checkbutton->_checked_highlight->setRelativeY(0);
    checkbutton->_checked_highlight->hide();

    checkbutton->_unchecked_texture = SolidImage::newSolidImage(unchecked_texture, width_height, width_height);
    checkbutton->_unchecked_texture->setParent(checkbutton);
    checkbutton->_unchecked_texture->setRelativeX(0);
    checkbutton->_unchecked_texture->setRelativeY(0);
    checkbutton->_unchecked_texture->show();

    checkbutton->_unchecked_highlight = SolidImage::newSolidImage(unchecked_hightlight, width_height, width_height);
    checkbutton->_unchecked_highlight->setParent(checkbutton);
    checkbutton->_unchecked_highlight->setRelativeX(0);
    checkbutton->_unchecked_highlight->setRelativeY(0);
    checkbutton->_unchecked_highlight->hide();

    checkbutton->_label = SolidText::newSolidText(label, font_name, font_size, font_color);
    checkbutton->_label->setParent(checkbutton);
    checkbutton->_label->setRelativeX(width_height + 10);
    checkbutton->_label->setRelativeY(width_height / 2 - checkbutton->_label->getHeight() / 2);

    checkbutton->_is_checked = false;

    checkbutton->hide();
    checkbutton->tie();

    return checkbutton;
}

void Checkbox::setCheckReaction(std::function<void(bool)> check_reaction)
{
    _check_reaction = check_reaction;
}

bool Checkbox::isChecked() const noexcept
{
    return _is_checked;
}

void Checkbox::check() noexcept
{
    if (isChecked())
        return;

    _is_checked = true;

    _checked_texture->show();
    _unchecked_texture->hide();
    _unchecked_highlight->hide();

    _check_reaction(true);
}

void Checkbox::uncheck() noexcept
{
    if (!isChecked())
        return;

    _is_checked = false;

    _checked_highlight->hide();
    _checked_texture->hide();
    _unchecked_texture->show();

    _check_reaction(false);
}

void Checkbox::hide()
{
    VisualComponent::hide();
    _checked_texture->hide();
    _checked_highlight->hide();
    _unchecked_highlight->hide();
    _unchecked_texture->hide();
    _label->hide();
}

void Checkbox::show()
{
    if (isChecked()) {
        _checked_texture->show();
        _label->show();
        _checked_highlight->hide();
        _unchecked_highlight->hide();
        _unchecked_texture->hide();
    } else {
        _checked_texture->hide();
        _label->show();
        _checked_highlight->hide();
        _unchecked_highlight->hide();
        _unchecked_texture->show();
    }
}

Checkbox::Checkbox(uint16_t width_height):
InteractiveComponent(width_height, width_height)
{

}

// Restricted
Checkbox::Checkbox(Checkbox & cpy):
InteractiveComponent(0, 0)
{

}

Checkbox::~Checkbox()
{

}

void Checkbox::reactToClick(const SDL_Point & cursor_coordinates)
{
    _is_checked = !_is_checked;
    if (_is_checked) {
        _checked_texture->show();
        _unchecked_texture->hide();
        _unchecked_highlight->hide();
    } else {
        _checked_highlight->hide();
        _checked_texture->hide();
        _unchecked_texture->show();
    }
    _check_reaction(_is_checked);
}

void Checkbox::reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    if (_is_checked)
        _checked_highlight->show();
    else
        _unchecked_highlight->show();
}

void Checkbox::reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates)
{
    if (_is_checked)
        _checked_highlight->hide();
    else
        _unchecked_highlight->hide();
}