#include "PageContainer.hpp"
#include "Helpers.hpp"

#include <iostream>

PageContainer * PageContainer::newPageContainer(uint16_t width,
                                                uint16_t height,
                                                uint16_t items_per_page,
                                                uint16_t pos_x,
                                                uint16_t pos_y)
{
    PageContainer * pc = new PageContainer(pos_x, pos_y, width, height, items_per_page);
    return pc;
}

void PageContainer::pushItem(InteractiveComponent * item) noexcept
{
    for (auto cell : _cells)
        if (item == cell->getItem())
            return;

    CellContainer * new_cell = CellContainer::newCellContainer(_items_width, _items_height, item);
    new_cell->setParent(this);

    uint16_t items_amount = _cells.size();
    if (items_amount % _items_per_page == 0) {
        new_cell->setRelativeX(0);
        new_cell->setRelativeY(0);
    }
    else {
        uint16_t prev_items_amount = items_amount;
        new_cell->setRelativeX(0);
        new_cell->setRelativeY((prev_items_amount % _items_per_page) * (5 + _items_height));
    }

    // Verify if this cell does not belong to displayed page
    if (!(items_amount >= pageDisplayed() * _items_per_page && items_amount < (pageDisplayed() + 1) * _items_per_page))
        new_cell->hide();

    _cells.push_back(new_cell);
}

void PageContainer::popItem(InteractiveComponent * item) noexcept
{
    // TODO
}

void PageContainer::hide() noexcept
{
    for (auto cell : _cells)
        cell->hideCell();
}

void PageContainer::show() noexcept
{
    int32_t bound_i = Helpers::min(int32_t((pageDisplayed() + 1) * _items_per_page), int32_t(_cells.size()));
    for (int32_t i = pageDisplayed() * _items_per_page; i < bound_i; i++)
        _cells[i]->showCell();
}

uint16_t PageContainer::pageDisplayed() const noexcept
{
    return _page_displayed;
}

void PageContainer::displayPage(const uint16_t page) noexcept
{
    _page_displayed = Helpers::min(int32_t(page), int32_t(getPagesQuantity()) - 1);
    PageContainer::hide();
    PageContainer::show();
}

uint16_t PageContainer::getPagesQuantity() const noexcept
{
    return _cells.size() / _items_per_page + (_cells.size() % _items_per_page > 0);
}

PageContainer::PageContainer(uint16_t pos_x,
                             uint16_t pos_y,
                             uint16_t width,
                             uint16_t height,
                             uint16_t items_per_page):
InteractiveComponent(width, height),
_cells(),
_page_displayed(0),
_items_per_page(items_per_page),
_items_width(width),
_items_height(height / items_per_page - (items_per_page - 1) * 5)
{
    VisualComponent::setInvisibility(true);
    VisualComponent::setDisplayCascade(true);
    InteractiveComponent::tie();
    InteractiveComponent::deactivate();
}

PageContainer::~PageContainer()
{

}