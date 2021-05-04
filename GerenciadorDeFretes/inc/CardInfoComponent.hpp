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
    void setCallBackClickReaction(std::function<void(void *)> call_back);

private:

    SolidImage * _image;
    std::vector<DynamicText *> _texts;
  
protected:
    CardInfoComponent(uint16_t width, uint16_t height, const std::string & image_name);
    std::function<void(void *)> _call_back;
    
    virtual ~CardInfoComponent();
    
    //The reaction when the component takes a mouse click
    virtual void reactToClick(const SDL_Point & cursor_coordinates) override;

    // The reaction when the mouse cursor is overlapping the component (with no clicks or pressings)
    virtual void reactToCursorOverlappingComponent(const SDL_Point & cursor_coordinates) override;

    // The reaction when the mouse cursor stops overlapping the component (with no clicks or pressings)
    virtual void reactToCursorStopedOverlappingComponent(const SDL_Point & cursor_coordinates) override;

};

#endif
