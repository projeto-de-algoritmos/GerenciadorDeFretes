#include "SliderContainer.hpp"
#include "Assets.hpp"
#include "Helpers.hpp"

SliderContainer * SliderContainer::newSliderContainer(uint16_t width,
                                                      uint16_t items_width,
                                                      uint16_t items_height)
{
    return new SliderContainer(width, items_width, items_height);
}

void SliderContainer::pushItem(InteractiveComponent * item)
{
    for (auto cell : _cells)
        if (cell->getItem() == item)
            return;

    CellContainer * new_cell = CellContainer::newCellContainer(_item_width, _item_height, item);
    if (_cells.empty()) {
        new_cell->setParent(this);
        new_cell->setRelativeX(VisualComponent::getWidth() / 2 - _item_width / 2);
        new_cell->setRelativeY(0);
    } else {
        new_cell->setParent(_cells.back());
        new_cell->setRelativeX(0);
        new_cell->setRelativeY(_cells.back()->getHeight());
    }
    if (_cells.size() % 2 == 0)
        new_cell->setColor({212, 250, 232, 255});
    else
        new_cell->setColor({237, 252, 247, 255});
    new_cell->setInvisibility(false);
    _cells.push_back(new_cell);
}

void SliderContainer::hide() noexcept
{
    VisualComponent::hide();
    InteractiveComponent::deactivate();

    for (auto cell : _cells)
        cell->hideCell();
}

void SliderContainer::show() noexcept
{
    VisualComponent::show();
    InteractiveComponent::activate();

    for (auto cell : _cells)
        cell->showCell();
}

SliderContainer::SliderContainer(uint16_t width,
                                 uint16_t items_width,
                                 uint16_t items_height):
InteractiveComponent(width, Assets::WINDOW_HEIGHT),
_item_width(items_width),
_item_height(items_height)
{
    VisualComponent::setColor({237, 252, 247, 255});
    VisualComponent::setInvisibility(false);
    VisualComponent::setDisplayCascade(true);
    InteractiveComponent::tie();
}

SliderContainer::~SliderContainer()
{

}

void SliderContainer::reactToFocusGaining()
{
    VisualComponent::setColor({212, 250, 232, 255});
}

void SliderContainer::reactToFocusLosing()
{
    VisualComponent::setColor({237, 252, 247, 255});
}

void SliderContainer::reactToScrolling(int32_t amount_scrolled)
{
    if (_cells.empty())
        return;
    _cells.front()->setRelativeY(_cells.front()->getRelativeY() + amount_scrolled);
    // Scroll up
    // if (amount_scrolled > 0 && _cells.front()->getRelativeY() < 5) {
    //     _cells.front()->setRelativeY(_cells.front()->getRelativeY() + amount_scrolled);
    //     _cells.front()->setRelativeY(Helpers::min(_cells.front()->getRelativeY() + amount_scrolled, 5));
    // }
    // // Scroll down
    // else if (amount_scrolled < 0 && _cells.back()->getRelativeY() + _cells.back()->getHeight() > VisualComponent::getHeight() - 5) {
    //     if (_cells.back()->getRelativeY() + amount_scrolled)
    //     _cells.front()->setRelativeY(Helpers::min(_cells.back()->getRelativeY() - 5, VisualComponent::getHeight() - 5 - _item_height));
    // }
}