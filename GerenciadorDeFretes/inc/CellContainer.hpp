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
    static CellContainer * newCellContainer(VisualComponent * item);

    // Create a new cell
    static CellContainer * newCellContainer(uint16_t width,
                                            uint16_t height,
                                            VisualComponent * item = nullptr,
                                            CellAlignment cell_alignment = MIDDLE_MIDDLE,
                                            int32_t pos_x = 0,
                                            int32_t pos_y = 0);

    VisualComponent * getItem() const noexcept;
    void setItem(VisualComponent * item) noexcept;

    void setWidth(uint16_t width) noexcept;
    void setHeight(uint16_t heigth) noexcept;

private:
    // Called whenever a new item is setted or cell is modified
    void updateCellDimensions() noexcept;

    CellContainer(uint16_t width = 0,
                  uint16_t height = 0, 
                  int32_t pos_x = 0,
                  int32_t pos_y = 0,
                  VisualComponent * item = nullptr,
                  CellAlignment cell_alignment = MIDDLE_MIDDLE);
    virtual ~CellContainer();

    VisualComponent * _item;
    CellAlignment _cell_alignment;

protected:

};

#endif