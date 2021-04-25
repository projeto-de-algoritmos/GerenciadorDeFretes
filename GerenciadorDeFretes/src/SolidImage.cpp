#include "SolidImage.hpp"
#include "AssetsManager.hpp"

SolidImage * SolidImage::newSolidImage(const std::string & image_name, uint16_t width, uint16_t height)
{
    return new SolidImage(width, height, AssetsManager::getInstance()->getTexture(image_name));
}

SolidImage::SolidImage(uint16_t width, uint16_t height, SDL_Texture * texture):
VisualComponent(width, height, {0xFF, 0xFF, 0xFF, 0xFF}, texture)
{

}

SolidImage::~SolidImage()
{

}
