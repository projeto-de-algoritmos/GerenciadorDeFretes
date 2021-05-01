#include "PageContainer.hpp"

PageContainer * PageContainer::newPageContainer(uint16_t pos_x,
                                                uint16_t pos_y,
                                                uint16_t width,
                                                uint16_t height,
                                                uint16_t items_per_page)
{
    PageContainer * pc = new PageContainer(pos_x, pos_y, width, height, items_per_page);
    return pc;
}

void PageContainer::pushItem(VisualComponent * item) noexcept
{
    for (auto cur_item : _items)
        if (item == cur_item)
            return;

    uint16_t items_amount = _items.size() + 1;
    if (items_amount % _items_per_page == 0) {
        item->setParent(this);
        item->setRelativeX(_items_width / 2 - item->getWidth() / 2);
        item->setRelativeY(_items_height / 2 - item->getHeight() / 2);
    }
    else {
        uint16_t prev_items_amount = items_amount - 1;
        item->setParent(this);
        item->setRelativeX(0);
        item->setRelativeY(((prev_items_amount) % _items_per_page) * (5 + _items_height));
    }
    item->setWidth(_items_width);
    item->setHeight(_items_height);
    //item->setDisplayCascade(true);
    _items.push_back(item);
}

void PageContainer::popItem(VisualComponent * item) noexcept
{
    // TODO
}

void PageContainer::hide() noexcept
{
    for (auto item : _items)
        item->hide();
}

void PageContainer::show() noexcept
{
    for (int32_t i = pageDisplayed() * _items_per_page; i < int32_t(pageDisplayed() + 1 * _items_per_page); i++)
        _items[i]->show();
}

uint16_t PageContainer::pageDisplayed() const noexcept
{
    return _page_displayed;
}

void PageContainer::displayPage(const uint16_t page) noexcept
{
    _page_displayed = page;
    PageContainer::hide();
    PageContainer::show();
}

PageContainer::PageContainer(uint16_t pos_x,
                             uint16_t pos_y,
                             uint16_t width,
                             uint16_t height,
                             uint16_t items_per_page):
VisualComponent(pos_x, pos_y),
_items(),
_page_displayed(0),
_items_per_page(items_per_page),
_items_width(_items_width),
_items_height(height / items_per_page - (items_per_page - 1) * 5)
{
    VisualComponent::hide();
}

PageContainer::~PageContainer()
{

}