#include "InteractiveComponent.hpp"
#include "Helpers.hpp"

#include <stdexcept>
#include <iostream>

InteractiveComponent * InteractiveComponent::NEUTRAL_COMPONENT = nullptr;
const std::string InteractiveComponent::ERROR_MSG = "\033[0;31m(ERROR) InteractiveComponent: \t\003[0m";

std::vector<InteractiveComponent *> InteractiveComponent::_components {};
InteractiveComponent * InteractiveComponent::_selected_component = nullptr;
InteractiveComponent * InteractiveComponent::_overlapped_component = nullptr;
InteractiveComponent * InteractiveComponent::_focused_component = nullptr;

void InteractiveComponent::startUp()
{
    if (NEUTRAL_COMPONENT != nullptr) {
        std::cerr << ERROR_MSG << " Attempt to start up more than once." << std::endl;
        throw std::runtime_error("InteractiveComponent exception");
    }

    NEUTRAL_COMPONENT = new InteractiveComponent(0,0);
    NEUTRAL_COMPONENT->deactivate();
    NEUTRAL_COMPONENT->tie();
    NEUTRAL_COMPONENT->setGlobalX(0);
    NEUTRAL_COMPONENT->setGlobalY(0);

    _selected_component = NEUTRAL_COMPONENT;
    _overlapped_component = NEUTRAL_COMPONENT;
    _focused_component = NEUTRAL_COMPONENT;
}

void InteractiveComponent::processMouseButtonDown(const SDL_Point & cursor_coordinates)
{
    if (NEUTRAL_COMPONENT == nullptr) {
        std::cerr << ERROR_MSG << "Attempt to call processMouseButtonDown before initialization." << std::endl;
        throw std::runtime_error("InteractiveComponent not initialized exception");
    }

    _selected_component = getComponentByClickCoordinates(cursor_coordinates);
    _selected_component->_initial_dragging_position = cursor_coordinates;
    _selected_component->_initial_hitbox_position = {
        _selected_component->getGlobalX(),
        _selected_component->getGlobalY()
    };
    _selected_component->reactToPressing(cursor_coordinates);
}

void InteractiveComponent::processMouseMotion(const SDL_Point & cursor_coordinates)
{
    if (NEUTRAL_COMPONENT == nullptr) {
        std::cerr << ERROR_MSG << "Attemtpt to call processMouseMotion before initialization";
        throw std::runtime_error("InteractiveComponent not initialized exception");
    }

    if (_selected_component != NEUTRAL_COMPONENT) {
        if (!_selected_component->isTied()) {
            int32_t delta_x = cursor_coordinates.x - _selected_component->_initial_dragging_position.x;
            int32_t delta_y = cursor_coordinates.y - _selected_component->_initial_dragging_position.y;
            int32_t x = delta_x + _selected_component->_initial_hitbox_position.x;
            int32_t y = delta_y + _selected_component->_initial_hitbox_position.y;
            
            VisualComponent * parent = _selected_component->getParent();
            x = Helpers::max(x, parent->getGlobalX());
            x = Helpers::min(x, parent->getGlobalX() + parent->getWidth() - _selected_component->getWidth());

            y = Helpers::max(y, parent->getGlobalY());
            y = Helpers::min(y, parent->getGlobalY() + parent->getHeight() - _selected_component->getHeight());
            
            _selected_component->setGlobalX(x);
            _selected_component->setGlobalY(y);
        }
        _selected_component->reactToDragging(cursor_coordinates);
    } else {
        InteractiveComponent * new_overlapped = getComponentByClickCoordinates(cursor_coordinates);
        if (new_overlapped != _overlapped_component) {
            new_overlapped->reactToCursorOverlappingComponent(cursor_coordinates);
            _overlapped_component->reactToCursorStopedOverlappingComponent(cursor_coordinates);
        }
        _overlapped_component = new_overlapped;
    }
}

void InteractiveComponent::processMouseButtonUp(const SDL_Point & cursor_coordinates)
{
    if (NEUTRAL_COMPONENT == nullptr) {
        std::cerr << ERROR_MSG << "Attempt to call processMouseButtonUp before initialization." << std::endl;
        throw std::runtime_error("InteractiveComponent not initialized exception");
    }

    int32_t delta_x = cursor_coordinates.x - _selected_component->_initial_dragging_position.x;
    int32_t delta_y = cursor_coordinates.y - _selected_component->_initial_dragging_position.y;
    if (SDL_abs(delta_x) <= 2 && SDL_abs(delta_y) <= 2) {
        _selected_component->reactToClick(cursor_coordinates);
        _focused_component = _selected_component;
    }
    
    _selected_component->reactToReleasing(cursor_coordinates);
    _selected_component = NEUTRAL_COMPONENT;
}

void InteractiveComponent::processKeyPressing(int32_t sdl_keysym)
{
    if (NEUTRAL_COMPONENT == nullptr) {
        std::cerr << ERROR_MSG << "Attempt to call processKeyPressing before initialization." << std::endl;
        throw std::runtime_error("InteractiveComponent not initialized exception");
    }

    _focused_component->reactToKeyPressing(sdl_keysym);
}

void InteractiveComponent::tie()
{
    _can_drag = false;
}

void InteractiveComponent::untie()
{
    _can_drag = true;
}

bool InteractiveComponent::isTied() const
{
    return !_can_drag;
}

void InteractiveComponent::activate()
{
    _is_active = true;
}

void InteractiveComponent::deactivate()
{
    _is_active = false;
}

bool InteractiveComponent::isActive() const
{
    return _is_active;
}

InteractiveComponent * InteractiveComponent::getComponentByClickCoordinates(const SDL_Point & coordinates)
{
    SDL_Rect component_rect;
    for (auto component : _components) {
        if (component->isActive() && (component_rect = component->getGlobalBody(), (SDL_PointInRect(&coordinates, &component_rect) == SDL_TRUE)))
            return component;
    }
    return NEUTRAL_COMPONENT;
}

InteractiveComponent::InteractiveComponent(uint16_t width, uint16_t height, SDL_Color color, SDL_Texture * texture):
VisualComponent(width, height, color, texture),
_initial_dragging_position({0,0}),
_initial_hitbox_position({0,0}),
_can_drag(true),
_is_active(true)
{
    _components.push_back(this);
}

InteractiveComponent::~InteractiveComponent()
{

}

void InteractiveComponent::reactToPressing(const SDL_Point & cursor_coordinates)
{

}

void InteractiveComponent::reactToReleasing(const SDL_Point & cursor_coordinates)
{

}

void InteractiveComponent::reactToClick(const SDL_Point & cursor_cordinates)
{

}

void InteractiveComponent::reactToDragging(const SDL_Point & cursor_coordinates)
{
    
}

void InteractiveComponent::reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates)
{

}

void InteractiveComponent::reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates)
{

}

void InteractiveComponent::reactToKeyPressing(int32_t sdl_keysym)
{

}