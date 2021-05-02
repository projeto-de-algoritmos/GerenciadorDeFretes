#include "VisualComponent.hpp"
#include "Graphics.hpp"

#include <stdexcept>
#include <iostream>

VisualComponent * VisualComponent::SCREEN = nullptr;
bool VisualComponent::VERBOSE = false;
const std::string VisualComponent::VERBOSE_MSG = "\033[0;33m(VERBOSE) VisualComponent:\t\033[0m";
const std::string VisualComponent::ERROR_MSG = "\033[0;31m(ERROR) VisualComponent:\t\033[0m";
Graphics * VisualComponent::graphics = nullptr;

void VisualComponent::setVerboseMode()
{
    VERBOSE = true;
}

void VisualComponent::startUp()
{
    if (SCREEN == nullptr) {
        graphics = Graphics::getInstance();
        SCREEN = new VisualComponent();
        SCREEN->setWidth(graphics->getWindowWidth());
        SCREEN->setHeight(graphics->getWindowHeight());

        if (VERBOSE) std::cout << VERBOSE_MSG << "Starting up" << std::endl;
    }
    else
        throwException("Attempt to initialize VisualComponent more than once");
}

void VisualComponent::shutDown()
{
    if (SCREEN == nullptr)
        throwException("Attempt to shut down VisualComponent before initialization");
    
    delete SCREEN;
    SCREEN = nullptr;
    graphics = nullptr;

    if (VERBOSE) std::cout << VERBOSE_MSG + "Shutting down\n" << std::endl; 
}

void VisualComponent::drawComponents()
{
    if (SCREEN == nullptr)
        throwException("Attempt to draw VisualComponent objects before initialization");
    
    graphics->clearScreen();
    SCREEN->draw();
    graphics->updateScreen();
}

VisualComponent * VisualComponent::getScreenObject()
{
    if (SCREEN == nullptr)
        throwException("Attempt to get VisualComponent SCREEN object before initialization");
    
    return SCREEN;
}

void VisualComponent::setParent(VisualComponent * new_parent)
{
    if (new_parent == _parent)
        return;
    else if (new_parent == nullptr || new_parent == NULL)
        throwException("Attempt to set VisualComponent object parent as nullptr");
    else if (new_parent == this)
        throwException("Attempt to set itself as a parent");
    else if (isAChild(new_parent))
        throwException("Attempt to set a child as a parent");

    if (_parent != nullptr)
        _parent->removeChild(this);

    new_parent->addChild(this);
    _parent = new_parent;
}

VisualComponent * VisualComponent::getParent() noexcept
{
    return _parent;
}

bool VisualComponent::isAChild(VisualComponent * component) const noexcept
{
    for (auto e : _children) {
        if (e == component)
            return true;
    }
    return false;
}

std::vector<VisualComponent *> VisualComponent::getChildren() const noexcept
{
    return _children;
}

int32_t VisualComponent::countChildren() const noexcept
{
    return (int32_t) _children.size();
}

void VisualComponent::hide() noexcept
{
    _is_hide = true;
}

void VisualComponent::show() noexcept
{
    _is_hide = false;
}

bool VisualComponent::isHide() const noexcept
{
    return _is_hide;
}

void VisualComponent::setTexture(SDL_Texture * texture) noexcept
{
    _texture = texture;
}

SDL_Texture * VisualComponent::getTexture() noexcept
{
    return _texture;
}

SDL_Rect VisualComponent::getGlobalBody() const noexcept
{
    if (_parent == nullptr)
        return _body;
   
    return {getGlobalX(), getGlobalY(), getWidth(), getHeight()};
}

SDL_Rect VisualComponent::getRelativeBody() const noexcept
{
    return _body;
}

int32_t VisualComponent::getGlobalX() const noexcept
{
    return (_parent == nullptr ? _body.x : _body.x + _parent->getGlobalX());
}

int32_t VisualComponent::getRelativeX() const noexcept
{
    return _body.x;
}

void VisualComponent::setGlobalX(int32_t x) noexcept
{
    if (_parent == nullptr)
        _body.x = x;
    else
        _body.x = x - _parent->getGlobalX();
}

void VisualComponent::setRelativeX(int32_t x) noexcept
{
    _body.x = x;
}

int32_t VisualComponent::getGlobalY() const noexcept
{
    return _parent == nullptr ? _body.y : _body.y + _parent->getGlobalY();
}

int32_t VisualComponent::getRelativeY() const noexcept
{
    return _body.y;
}

void VisualComponent::setGlobalY(int32_t y) noexcept
{
    if (_parent == nullptr)
        _body.y = y;
    else
        _body.y = y - _parent->getGlobalY();
}

void VisualComponent::setRelativeY(int32_t y) noexcept
{
    _body.y = y;
}

uint16_t VisualComponent::getWidth() const noexcept
{
    return _body.w;
}

void VisualComponent::setWidth(uint16_t width) noexcept
{
    _body.w = width;
}

uint16_t VisualComponent::getHeight() const noexcept
{
    return _body.h;
}

void VisualComponent::setHeight(uint16_t height) noexcept
{
    _body.h = height;
}

double VisualComponent::getRotationAngle() const noexcept
{
    return _rotation_angle;
}

void VisualComponent::setRotationAngle(double rotation_angle) noexcept
{
    _rotation_angle = rotation_angle;
}

void VisualComponent::rotateClockwise(double amount) noexcept
{
    setRotationAngle(getRotationAngle() + amount);
    for (auto child : _children)
        child->rotateClockwise(amount);
}

SDL_Color VisualComponent::getColor() const noexcept
{
    return _color;
}

void VisualComponent::setColor(SDL_Color color) noexcept
{
    _color = color;
}

void VisualComponent::addChild(VisualComponent * child)
{
    if (child == nullptr)
        throwException("Attempt to push nullptr as a child");
    else if (child == this)
        throwException("Attempt to push itself as a child");
    else if (child == getParent())
        throwException("Attempt to push parent as a child");

    for (auto e : _children) {
        if (e == child)
            return;
    }
    _children.push_back(child);
}

void VisualComponent::removeChild(VisualComponent * child)
{
    auto iter = _children.begin();
    for ( ; iter != _children.end(); iter++)
        if (*iter == child) break;
    if (iter != _children.end())
        _children.erase(iter);
}

void VisualComponent::draw()
{
    if (_texture != nullptr && !_is_hide && !_invisible)
        graphics->drawTexture(_texture, getGlobalBody(), getRotationAngle());

    else if (_texture == nullptr && !_is_hide && !_invisible)
        graphics->drawRectangle(getGlobalBody(), _color);
    
    if (_display_cascate && _is_hide)
        return;
    
    for (auto child : _children)
        child->draw();
}

void VisualComponent::setDisplayCascade(bool enable)
{
    _display_cascate = enable;
}

void VisualComponent::setInvisibility(bool enable)
{
    _invisible = enable;
}

void VisualComponent::throwException(const std::string & msg)
{
    std::cerr << ERROR_MSG << msg << std::endl;
    throw std::runtime_error("VisualComponent exception");
}

VisualComponent::VisualComponent():
_children(),
_parent(nullptr),
_texture(nullptr),
_rotation_angle(0.0),
_is_hide(false),
_body({0,0,0,0}),
_color({0xff, 0xff, 0xff, 0xff}),
_display_cascate(false)
{

}

VisualComponent::VisualComponent(uint16_t width, uint16_t height, SDL_Color color, SDL_Texture * texture):
_children(),
_parent(nullptr),
_texture(texture),
_rotation_angle(0.0),
_is_hide(false),
_body({0, 0, width, height}),
_color(color),
_display_cascate(false),
_invisible(false)
{
    setParent(getScreenObject());
}

VisualComponent::~VisualComponent()
{
    for (auto child : _children) {
        
        if (VERBOSE) {
            std::cout << VERBOSE_MSG + "Deleting this component:" << std::endl;

            graphics->clearScreen();
            if (child->getTexture() != nullptr)
                graphics->drawTexture(child->getTexture(), child->getGlobalBody());
            graphics->updateScreen();
            SDL_Delay(500);
        }

        delete child;
    }
}
