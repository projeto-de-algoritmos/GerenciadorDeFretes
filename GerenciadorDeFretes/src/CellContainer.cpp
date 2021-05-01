#include <stdexcept>

#include "CellContainer.hpp"
#include "Helpers.hpp"

CellContainer * CellContainer::newCellContainer(VisualComponent * item)
{
    if (item == nullptr)
        throw std::runtime_error("Attempt to create a cell container based on nullptr item");

    return new CellContainer(item->getWidth(), item->getHeight(), 0, 0, item);
}

CellContainer * CellContainer::newCellContainer(uint16_t width,
                                                uint16_t height,
                                                CellAlignment cell_alignment,
                                                VisualComponent * item,
                                                int32_t pos_x,
                                                int32_t pos_y)
{
    return new CellContainer(width, height, pos_x, pos_y, item, cell_alignment;
}

VisualComponent * CellContainer::getItem() const noexcept
{
    return _item;
}

void CellContainer::setItem(VisualComponent * item) noexcept
{
    if (item == getItem())
        return;

    _item = item;
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
                             VisualComponent * item,
                             CellAlignment cell_alignment):
InteractiveComponent(width, height),
_item(item),
_cell_alignment(cell_alignment)
{
    setDisplayCascade(true);
    tie();
    updateCellDimensions();
}

