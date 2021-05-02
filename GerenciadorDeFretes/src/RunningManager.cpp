#include "RunningManager.hpp"
#include "TextField.hpp"
#include "PageContainer.hpp"
#include "CellContainer.hpp"
#include "SliderContainer.hpp"

#include <iostream>

static Timer timer;
static bool program_running = true;
static SDL_Event event;

static PageContainer * side_bar = nullptr;
static CellContainer * main_menu = nullptr;

static SliderContainer * sc;

void RunningManager::StartFrame()
{
    double_t elapsed_time = timer.getElapsedTime();
    if (elapsed_time < Assets::_60_FPS_FRAMETIME)
        SDL_Delay(int32_t((Assets::_60_FPS_FRAMETIME - elapsed_time) * 1000.0));
    
    timer.reset();
}

void RunningManager::FinishFrame()
{

}

void RunningManager::HandleUserInput()
{
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            FinishProgramExecution();
            break;
        case SDL_KEYDOWN:
            InteractiveComponent::processKeyPressing(event.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            InteractiveComponent::processMouseButtonDown({event.button.x, event.button.y});
            break;
        case SDL_MOUSEBUTTONUP:
            InteractiveComponent::processMouseButtonUp({event.button.x, event.button.y});
            break;
        case SDL_MOUSEMOTION:
            InteractiveComponent::processMouseMotion({event.motion.x, event.motion.y});
            break;
        case SDL_MOUSEWHEEL:
            InteractiveComponent::processMouseScrolling(event.wheel.y * 30);
            break;
        default:
            break;
        }
    }
}

void RunningManager::FinishProgramExecution()
{
    program_running = false;
}

bool RunningManager::ProgramIsRunning()
{
    return program_running;
}

void RunningManager::StartDependencies()
{
    Graphics::startUp();
    VisualComponent::startUp();
    InteractiveComponent::startUp();
}

void RunningManager::SetVerboseMode()
{
    AssetsManager::setVerboseMode();
    VisualComponent::setVerboseMode();
}

void RunningManager::ReleaseDependencies()
{
    VisualComponent::shutDown();
    AssetsManager::shutDown();
    Graphics::shutDown();
}

void RunningManager::RenderScreen()
{
    VisualComponent::drawComponents();
}

void ShowDriversPage()
{

}

void ShowDeliveriesPage()
{

}

void RunningManager::InitializeUIElments()
{
    side_bar = PageContainer::newPageContainer(Assets::BUTTON_WIDTH + 10, Assets::WINDOW_HEIGHT, 5);
    side_bar->setColor({163, 204, 186, 255});
    side_bar->setInvisibility(false);
    side_bar->show();
    
    Button * button;

    button = Button::newButton("Motoristas");
    button->setClickReaction(ShowDriversPage);
    side_bar->pushItem(button);

    button = Button::newButton("Fretes");
    button->setClickReaction(ShowDeliveriesPage);
    side_bar->pushItem(button);

    button = Button::newButton("Sair");
    button->setClickReaction(RunningManager::FinishProgramExecution);
    side_bar->pushItem(button);

    // main_menu = CellContainer::newCellContainer(Assets::WINDOW_WIDTH - side_bar->getWidth(), Assets::WINDOW_HEIGHT, SolidImage::newSolidImage("Delivery.jpg", 425, 300));
    // main_menu->setRelativeX(side_bar->getWidth());
    // main_menu->setRelativeY(0);

    sc = SliderContainer::newSliderContainer(Assets::WINDOW_WIDTH - side_bar->getWidth(), 200, 80);
    sc->pushItem(Button::newButton("Ola xapa"));
    sc->pushItem(SolidImage::newSolidImage("delivery_logo.png", 80, 80));
    sc->pushItem(SolidText::newSolidText("Respeita", "arial.ttf", 20, {0,0,0,255}));
    sc->pushItem(TextField::newTextField());
    sc->pushItem(Button::newButton("kkkkk"));
    sc->pushItem(SolidImage::newSolidImage("delivery_logo.png", 80, 80));
    sc->pushItem(SolidImage::newSolidImage("delivery_logo.png", 80, 80));
    sc->pushItem(SolidImage::newSolidImage("delivery_logo.png", 80, 80));

    main_menu = CellContainer::newCellContainer(Assets::WINDOW_WIDTH - side_bar->getWidth(), Assets::WINDOW_HEIGHT, sc);
    main_menu->setRelativeX(side_bar->getWidth());
    main_menu->setRelativeY(0);
}