#ifndef _SLIDER_CONTAINER_HPP_
#define _SLIDER_CONTAINER_HPP_

#include "CellContainer.hpp"
#include "InteractiveComponent.hpp"

#include <cstdint>
#include <vector>

class SliderContainer : public InteractiveComponent
{
public:
    static SliderContainer * newSliderContainer(uint16_t width,
                                                uint16_t items_width,
                                                uint16_t items_height);

    void pushItem(InteractiveComponent * item);

    void hide() noexcept;
    void show() noexcept;

private:
    SliderContainer(uint16_t width = 0, uint16_t items_width = 0, uint16_t items_height = 0);
    virtual ~SliderContainer();

    uint16_t _item_width;
    uint16_t _item_height;
    std::vector<CellContainer *> _cells;

protected:
    virtual void reactToFocusGaining() override;

    virtual void reactToFocusLosing() override;

    virtual void reactToScrolling(int32_t amount_scrolled) override;
};

#endif