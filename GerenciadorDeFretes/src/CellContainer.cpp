#include <stdexcept>
#include <iostream>

#include "CellContainer.hpp"
#include "Helpers.hpp"

CellContainer * CellContainer::newCellContainer(InteractiveComponent * item)
{
    if (item == nullptr)
        throw std::runtime_error("Attempt to create a cell container based on nullptr item");

    return new CellContainer(item->getWidth(), item->getHeight(), 0, 0, item);
}

CellContainer * CellContainer::newCellContainer(uint16_t width,
                                                uint16_t height,
                                                InteractiveComponent * item,
                                                CellAlignment cell_alignment,
                                                int32_t pos_x,
                                                int32_t pos_y)
{
    return new CellContainer(width, height, pos_x, pos_y, item, cell_alignment);
}

InteractiveComponent * CellContainer::getItem() const noexcept
{
    return _item;
}

void CellContainer::setItem(InteractiveComponent * item) noexcept
{
    if (item == getItem())
        return;

    _item = item;
    _item->setParent(this);
    updateCellDimensions();
}

void CellContainer::setWidth(uint16_t width) noexcept
{
    VisualComponent::setWidth(width);
    updateCellDimensions();
}

void CellContainer::setHeight(uint16_t height) noexcept
{
    VisualComponent::setHeight(height);
    updateCellDimensions();
}

void CellContainer::hideCell() noexcept
{
    VisualComponent::hide();
    _item->deactivate();
}

void CellContainer::showCell() noexcept
{
    VisualComponent::show();
    if (_item_is_active)
        _item->activate();
}

CellContainer::CellAlignment CellContainer::getCellAlignment() const noexcept
{
    return _cell_alignment;
}

void CellContainer::setCellAlignment(CellAlignment cell_alignment) noexcept
{
    _cell_alignment = cell_alignment;
    updateCellDimensions();
}

void CellContainer::updateCellDimensions() noexcept
{
    if (getItem() == nullptr)
        return;
    
    // Expand cell to comport its item (if necessary)
    VisualComponent::setWidth(Helpers::max(VisualComponent::getWidth(), _item->getWidth()));
    VisualComponent::setHeight(Helpers::max(VisualComponent::getHeight(), _item->getHeight()));

    switch (_cell_alignment)
    {
    case CellAlignment::TOP_LEFT:
        _item->setRelativeX(0);
        _item->setRelativeY(0);
        break;

    case CellAlignment::TOP_MIDDLE:
        _item->setRelativeX(VisualComponent::getWidth() / 2 - _item->getWidth() / 2);
        _item->setRelativeY(0);
        break;

    case CellAlignment::TOP_RIGTH:
        _item->setRelativeX(VisualComponent::getWidth() - _item->getWidth());
        _item->setRelativeY(0);
        break;

    case CellAlignment::MIDDLE_LEFT:
        _item->setRelativeX(0);
        _item->setRelativeY(VisualComponent::getHeight() / 2 - _item->getHeight() / 2);
        break;

    case CellAlignment::MIDDLE_MIDDLE:
        _item->setRelativeX(VisualComponent::getWidth() / 2 - _item->getWidth() / 2);
        _item->setRelativeY(VisualComponent::getHeight() / 2 - _item->getHeight() / 2);
        break;

    case CellAlignment::MIDDLE_RIGHT:
        _item->setRelativeX(VisualComponent::getWidth() - _item->getWidth());
        _item->setRelativeY(VisualComponent::getHeight() / 2 - _item->getHeight() / 2);
        break;

    case CellAlignment::BOTTOM_LEFT:
        _item->setRelativeX(0);
        _item->setRelativeY(VisualComponent::getHeight() - _item->getHeight());
        break;

    case CellAlignment::BOTTOM_MIDDLE:
        _item->setRelativeX(VisualComponent::getWidth() / 2 - _item->getWidth() / 2);
        _item->setRelativeY(VisualComponent::getHeight() - _item->getHeight());
        break;

    case CellAlignment::BOTTOM_RIGHT:
        _item->setRelativeX(VisualComponent::getWidth() - _item->getWidth());
        _item->setRelativeY(VisualComponent::getHeight() - _item->getHeight());
        break;
    
    default:
        break;
    }
}

CellContainer::CellContainer(uint16_t width,
                             uint16_t height,
                             int32_t pos_x,
                             int32_t pos_y,
                             InteractiveComponent * item,
                             CellAlignment cell_alignment):
InteractiveComponent(width, height),
_item(item),
_cell_alignment(cell_alignment),
_item_is_active(_item->isActive())
{
    VisualComponent::setInvisibility(true);
    VisualComponent::setDisplayCascade(true);
    InteractiveComponent::tie();
    InteractiveComponent::deactivate();
    _item->setParent(this);
    updateCellDimensions();
}

CellContainer::~CellContainer()
{

}