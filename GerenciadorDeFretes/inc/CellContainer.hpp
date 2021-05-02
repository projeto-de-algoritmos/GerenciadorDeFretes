#ifndef _CELL_CONTAINER_HPP_
#define _CELL_CONTAINER_HPP_

#include "InteractiveComponent.hpp"

// This class is a wrapper for any kind of visual component
// It allows us to insert and manipulate any visual component despite
// its properties
class CellContainer : public InteractiveComponent
{
public:
    enum CellAlignment
    {
        TOP_LEFT,
        TOP_RIGTH,
        TOP_MIDDLE,
        MIDDLE_LEFT,
        MIDDLE_MIDDLE,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_MIDDLE,
        BOTTOM_RIGHT
    };

    // Create a new Cell based on item's shape
    static CellContainer * newCellContainer(InteractiveComponent * item);

    // Create a new cell for visual component item
    static CellContainer * newCellContainer(uint16_t width,
                                            uint16_t height,
                                            InteractiveComponent * item = nullptr,
                                            CellAlignment cell_alignment = MIDDLE_MIDDLE,
                                            int32_t pos_x = 0,
                                            int32_t pos_y = 0);

    InteractiveComponent * getItem() const noexcept;
    void setItem(InteractiveComponent * item) noexcept;

    void setWidth(uint16_t width) noexcept;
    void setHeight(uint16_t heigth) noexcept;

    void hideCell() noexcept;
    void showCell() noexcept;

    CellAlignment getCellAlignment() const noexcept;
    void setCellAlignment(CellAlignment cell_alignment) noexcept;

private:
    // Called whenever a new item is setted or cell is modified
    void updateCellDimensions() noexcept;

    CellContainer(uint16_t width = 0,
                  uint16_t height = 0, 
                  int32_t pos_x = 0,
                  int32_t pos_y = 0,
                  InteractiveComponent * item = nullptr,
                  CellAlignment cell_alignment = MIDDLE_MIDDLE);
    virtual ~CellContainer();

    InteractiveComponent * _item;
    CellAlignment _cell_alignment;
    bool _item_is_active;

protected:

};

#endif