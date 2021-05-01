#ifndef _PAGE_CONTAINER_HPP_
#define _PAGE_CONTAINER_HPP_

#include "VisualComponent.hpp"

#include <vector>
#include <cstdint>

class PageContainer : public VisualComponent
{
public:
    static PageContainer * newPageContainer(uint16_t pos_x,
                                            uint16_t pos_y,
                                            uint16_t width,
                                            uint16_t height,
                                            uint16_t items_per_page);

    void pushItem(VisualComponent * item) noexcept;
    void popItem(VisualComponent * item) noexcept;

    void hide() noexcept;
    void show() noexcept;

    uint16_t pageDisplayed() const noexcept;
    void displayPage(const uint16_t page) noexcept;

private:
    PageContainer();
    PageContainer(uint16_t pos_x,
                  uint16_t pos_y,
                  uint16_t width,
                  uint16_t height,
                  uint16_t items_per_page
                  );

    virtual ~PageContainer();

    std::vector<VisualComponent *> _items;
    uint16_t _page_displayed;
    uint16_t _items_per_page;
    uint16_t _items_width;
    uint16_t _items_height;

protected:

};

#endif