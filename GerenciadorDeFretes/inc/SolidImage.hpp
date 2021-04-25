#ifndef _SOLIDIMAGE_HPP_
#define _SOLIDIMAGE_HPP_

#include "VisualComponent.hpp"
#include <string>

class SolidImage : public VisualComponent
{
public:
    static SolidImage * newSolidImage(const std::string & image_name, uint16_t width, uint16_t height);

private:
    SolidImage(uint16_t width = 0, uint16_t height = 0, SDL_Texture * texture = nullptr);
    virtual ~SolidImage();
};

#endif