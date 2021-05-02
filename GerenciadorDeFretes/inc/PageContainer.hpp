#ifndef _PAGE_CONTAINER_HPP_
#define _PAGE_CONTAINER_HPP_

#include "VisualComponent.hpp"
#include "CellContainer.hpp"

#include <vector>
#include <cstdint>

class PageContainer : public InteractiveComponent
{
public:
    static PageContainer * newPageContainer(uint16_t width,
                                            uint16_t height,
                                            uint16_t items_per_page,
                                            uint16_t pos_x = 0,
                                            uint16_t pos_y = 0);

    void pushItem(InteractiveComponent * item) noexcept;
    void popItem(InteractiveComponent * item) noexcept;

    void hide() noexcept;
    void show() noexcept;

    uint16_t pageDisplayed() const noexcept;
    void displayPage(const uint16_t page) noexcept;

    uint16_t getPagesQuantity() const noexcept;

private:
    PageContainer();
    PageContainer(uint16_t pos_x,
                  uint16_t pos_y,
                  uint16_t width,
                  uint16_t height,
                  uint16_t items_per_page
                  );

    virtual ~PageContainer();

    std::vector<CellContainer *> _cells;
    uint16_t _page_displayed;
    uint16_t _items_per_page;
    uint16_t _items_width;
    uint16_t _items_height;

protected:

};

#endif