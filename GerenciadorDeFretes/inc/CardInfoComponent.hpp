#ifndef _CARD_INFO_COMPONENT_HPP_
#define _CARD_INFO_COMPONENT_HPP_

#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "DynamicText.hpp"

#include <vector>
#include <functional>

class CardInfoComponent : public InteractiveComponent
{
public:
    static CardInfoComponent * newCardInfoComponent(uint16_t width, uint16_t height, const std::string & image_name);

    void pushText(const std::string & text);
    void updateText(int32_t index, const std::string & text);
    void setCallBackClickReaction(std::function<void()> call_back);

private:
    CardInfoComponent(uint16_t width, uint16_t height, const std::string & image_name);
    virtual ~CardInfoComponent();

    std::function<void()> _call_back;
    SolidImage * _image;
    std::vector<DynamicText *> _texts;
  
protected:


};

#endif
