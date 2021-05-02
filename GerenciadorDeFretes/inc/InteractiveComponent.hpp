#ifndef _INTERACTIVECOMPONENT_HPP_
#define _INTERACTIVECOMPONENT_HPP_

#include <SDL2/SDL.h>
#include "VisualComponent.hpp"

#include <vector>
#include <functional>
#include <string>

// Allow click detection, dragging events and state changes
class InteractiveComponent : public VisualComponent
{
public:
    static void startUp();

    static void processMouseButtonDown(const SDL_Point & cursor_coordinates);
    static void processMouseMotion(const SDL_Point & cursor_coordinates);
    static void processMouseButtonUp(const SDL_Point & cursor_coordinates);
    static void processKeyPressing(int32_t sdl_keysym);
    static void processMouseScrolling(int32_t amount_scrolled);

    void tie();
    void untie();
    bool isTied() const;

    void activate();
    void deactivate();
    bool isActive() const;

    bool isFocused() const;
    void setFocus();

private:
    static InteractiveComponent * getComponentByClickCoordinates(const SDL_Point & coordinates);

    static InteractiveComponent * NEUTRAL_COMPONENT;
    static const std::string ERROR_MSG;
    
    static std::vector<InteractiveComponent *> _components;
    static InteractiveComponent * _selected_component;
    static InteractiveComponent * _overlapped_component;
    static InteractiveComponent * _focused_component;

    InteractiveComponent();
    InteractiveComponent(const InteractiveComponent & cpy);

    SDL_Point _initial_dragging_position;
    SDL_Point _initial_hitbox_position;
    bool _can_drag;
    bool _is_active;

protected:
    InteractiveComponent(uint16_t width,
                         uint16_t height,
                         SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF},
                         SDL_Texture * texture = nullptr);

    virtual ~InteractiveComponent();

    //The reaction when mouse button is pressed on the component
    virtual void reactToPressing(const SDL_Point & cursor_coordinates);

    //The reaction when mouse button is released after a previous
    //pressing on the component
    virtual void reactToReleasing(const SDL_Point & cursor_coordinates);

    //The reaction when the component takes a mouse click
    virtual void reactToClick(const SDL_Point & cursor_coordinates);

    //The reaction when the component is being dragged
    virtual void reactToDragging(const SDL_Point & cursor_coordinates);

    // The reaction when the mouse cursor is overlapping the component (with no clicks or pressings)
    virtual void reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates);

    // The reaction when the mouse cursor stops overlapping the component (with no clicks or pressings)
    virtual void reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates);

    // The reaction when a key from keyboard is pressed
    virtual void reactToKeyPressing(int32_t sdl_keysym);

    // The reaction when this component gain focus
    virtual void reactToFocusGaining();

    // The reaction when this component loses focus
    virtual void reactToFocusLosing();

    // The reaction when the focused component receives scroll
    virtual void reactToScrolling(int32_t amount_scrolled);
};

#endif