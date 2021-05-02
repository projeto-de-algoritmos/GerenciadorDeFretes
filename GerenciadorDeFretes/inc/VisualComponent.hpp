#ifndef _VISUAL_COMPONENT_HPP_
#define _VISUAL_COMPONENT_HPP_

#include "Graphics.hpp"
#include <SDL2/SDL.h>

#include <vector>
#include <string>

class VisualComponent
{
public:
    static void setVerboseMode();

    static void startUp();
    static void shutDown();
    static void drawComponents();
    static VisualComponent * getScreenObject();

    void setParent(VisualComponent * new_parent);
    VisualComponent * getParent() noexcept;

    bool isAChild(VisualComponent * component) const noexcept;

    std::vector<VisualComponent *> getChildren() const noexcept;
    int32_t countChildren() const noexcept;

    void hide() noexcept;
    void show() noexcept;
    bool isHide() const noexcept;

    void setTexture(SDL_Texture * texture) noexcept;
    SDL_Texture * getTexture() noexcept;

    SDL_Rect getGlobalBody() const noexcept;
    SDL_Rect getRelativeBody() const noexcept;

    int32_t getGlobalX() const noexcept;
    int32_t getRelativeX() const noexcept;
    void setGlobalX(int32_t x) noexcept;
    void setRelativeX(int32_t x) noexcept;

    int32_t getGlobalY() const noexcept;
    int32_t getRelativeY() const noexcept;
    void setGlobalY(int32_t y) noexcept;
    void setRelativeY(int32_t y) noexcept;

    uint16_t getWidth() const noexcept;
    void setWidth(uint16_t width) noexcept;

    uint16_t getHeight() const noexcept;
    void setHeight(uint16_t height) noexcept;

    double getRotationAngle() const noexcept;
    void setRotationAngle(double rotation_angle) noexcept;
    void rotateClockwise(double amount) noexcept;

    SDL_Color getColor() const noexcept;
    void setColor(SDL_Color color) noexcept;

    void addChild(VisualComponent * child);
    void removeChild(VisualComponent * child);
    
    void draw();

    void setDisplayCascade(bool enable);
    void setInvisibility(bool enable);

private:
    static VisualComponent * SCREEN;
    static bool VERBOSE;
    static const std::string VERBOSE_MSG;
    static const std::string ERROR_MSG;
    static Graphics * graphics;
    static void throwException(const std::string & msg);

    VisualComponent();
    
    std::vector<VisualComponent *> _children;
    VisualComponent * _parent;
    SDL_Texture * _texture;
    double _rotation_angle;
    bool _is_hide;
    SDL_Rect _body;
    SDL_Color _color;
    bool _display_cascate;
    bool _invisible;

protected:

    VisualComponent(uint16_t width, uint16_t height,
                    SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF},
                    SDL_Texture * texture = nullptr);

    virtual ~VisualComponent();
};

#endif