#include "RunningManager.hpp"
#include "TextField.hpp"
#include "PageContainer.hpp"
#include "CellContainer.hpp"
#include "SliderContainer.hpp"
#include "CardInfoComponent.hpp"
#include "DeliveryInfoCard.hpp"
#include "DriverInfoCard.hpp"
#include "DeliveryPlanning.hpp"

#include <utility>
#include <cstdlib>
#include <iostream>

static Timer timer;
static bool program_running = true;
static SDL_Event event;

static CellContainer * main_menu = nullptr;
static Button * quit_button;
static Button * start_button;

static std::vector<std::pair<Driver *, DriverInfoCard *>> drivers;

static PageContainer * drivers_menu;
static Button * drivers_menu_next_page;
static Button * drivers_menu_previous_page;
static DynamicText * drivers_menu_current_page;

static Button * create_driver;
static Button * see_deliveries;

static SolidText * new_driver_name;
static SolidText * new_driver_age;
static SolidText * new_driver_vehicle;
static TextField * new_driver_name_field;
static TextField * new_driver_age_field;
static TextField * new_driver_vehicle_field;
static Button * new_driver_confirm;
static Driver * new_driver;

static std::vector<std::pair<Delivery *, DeliveryInfoCard *>> deliveries;
static SliderContainer * deliveries_menu;
static Button * planning_button;
static SolidText * profit_total;

static SliderContainer * drivers_deliveries_menu;
static std::vector<CardInfoComponent *> planning_cards;

static void ShowDriverUpdateElements();
static void HideDriverUpdateElements();
static void CreateDriver();
static void ConfirmDriver();
static void ShowDeliveries();
static void ShowPlanning();

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
    main_menu->hide();

    quit_button->hide();
    quit_button->deactivate();

    start_button->hide();
    start_button->deactivate();

    drivers_menu_previous_page->show();
    drivers_menu_previous_page->activate();
    drivers_menu_current_page->show();
    drivers_menu_next_page->show();
    drivers_menu_next_page->activate();
    drivers_menu->show();

    create_driver->show();
    create_driver->activate();

    see_deliveries->show();
    see_deliveries->activate();
}

void NextPageDriversMenu()
{
    if (drivers_menu->pageDisplayed() + 1 >= drivers_menu->getPagesQuantity())
        return;

    drivers_menu->displayPage(drivers_menu->pageDisplayed() + 1);
    drivers_menu_current_page->setText("Pag. " + std::to_string(drivers_menu->pageDisplayed()));
}

void PreviousPageDriversMenu()
{
    if (drivers_menu->pageDisplayed() == 0)
        return;

    drivers_menu->displayPage(drivers_menu->pageDisplayed() - 1);
    drivers_menu_current_page->setText("Pag. " + std::to_string(drivers_menu->pageDisplayed()));
}

void CreateDriver()
{
    new_driver = new Driver("name", 1, "vehicle");

    drivers_menu_previous_page->hide();
    drivers_menu_previous_page->deactivate();
    drivers_menu_current_page->hide();
    drivers_menu_next_page->hide();
    drivers_menu_next_page->deactivate();
    drivers_menu->hide();

    create_driver->hide();
    create_driver->deactivate();

    see_deliveries->hide();
    see_deliveries->deactivate();

    ShowDriverUpdateElements();
}

void ShowDriverUpdateElements()
{
    new_driver_name->show();
    new_driver_name_field->show();
    new_driver_name_field->activate();

    new_driver_age->show();
    new_driver_age_field->show();
    new_driver_age_field->activate();

    new_driver_vehicle->show();
    new_driver_vehicle_field->show();
    new_driver_vehicle_field->activate();

    new_driver_confirm->show();
    new_driver_confirm->activate();
}

void HideDriverUpdateElements()
{
    new_driver_name->hide();
    new_driver_name_field->hide();
    new_driver_name_field->deactivate();

    new_driver_age->hide();
    new_driver_age_field->hide();
    new_driver_age_field->deactivate();

    new_driver_vehicle->hide();
    new_driver_vehicle_field->hide();
    new_driver_vehicle_field->deactivate();

    new_driver_confirm->hide();
    new_driver_confirm->deactivate();
}

void ConfirmDriver()
{
    new_driver->setDriverName(new_driver_name_field->getContent());
    new_driver->setDriverVehicleName(new_driver_vehicle_field->getContent());
    new_driver->setDriverAge(std::stod(new_driver_age_field->getContent()));
    
    drivers.push_back({new_driver, DriverInfoCard::newDriverInfoCard(new_driver, 300, 100)});
    drivers_menu->pushItem(drivers.back().second);

    HideDriverUpdateElements();
    ShowDriversPage();
}

void ShowDeliveries()
{
    drivers_menu_previous_page->hide();
    drivers_menu_previous_page->deactivate();
    drivers_menu_current_page->hide();
    drivers_menu_next_page->hide();
    drivers_menu_next_page->deactivate();
    drivers_menu->hide();

    create_driver->hide();
    create_driver->deactivate();

    see_deliveries->hide();
    see_deliveries->deactivate();

    deliveries_menu->show();
    planning_button->show();
    planning_button->activate();
}

void ShowPlanning()
{
    deliveries_menu->hide();
    planning_button->hide();
    planning_button->hide();

    std::vector<Driver *> t_drivers;
    for (auto driver : drivers)
        t_drivers.push_back(driver.first);

    std::vector<Delivery *> t_delivery;
    for (auto delivery : deliveries)
        t_delivery.push_back(delivery.first);
    
    std::vector<std::pair<Driver *, Delivery *>> result = DeliveryPlanning::SolveDeliveryPlanning(t_drivers, t_delivery);
    double total = 0;
    for (auto pi : result) {
        CardInfoComponent * cic = CardInfoComponent::newCardInfoComponent(400, 110, "delivery_logo.png");
        cic->pushText("Entrega: " + pi.second->getName());
        cic->pushText("Motorista: " + pi.first->getDriverName());
        cic->pushText("Lucro: R$ " + std::to_string(pi.second->getProfit()));
        total += pi.second->getProfit();
        planning_cards.push_back(cic);
    }

    drivers_deliveries_menu = SliderContainer::newSliderContainer(Assets::WINDOW_WIDTH, 400, 110);
    for (auto card : planning_cards)
        drivers_deliveries_menu->pushItem(card);

    profit_total = SolidText::newSolidText("Total: R$" + std::to_string(total));
    profit_total->setRelativeX(Assets::WINDOW_WIDTH - profit_total->getWidth() - 10);
    profit_total->setRelativeY(Assets::WINDOW_HEIGHT - profit_total->getHeight() - 10);
}

void RunningManager::InitializeUIElments()
{   
    main_menu = CellContainer::newCellContainer(Assets::WINDOW_WIDTH, Assets::WINDOW_HEIGHT, SolidImage::newSolidImage("Delivery.jpg", 425, 300));
    main_menu->setRelativeX(0);
    main_menu->setRelativeY(0);

    quit_button = Button::newButton("Sair");
    quit_button->setClickReaction(FinishProgramExecution);
    quit_button->setRelativeX(Assets::WINDOW_WIDTH / 2 - quit_button->getWidth() / 2);
    quit_button->setRelativeY(Assets::WINDOW_HEIGHT - quit_button->getHeight() - 10);

    start_button = Button::newButton("Iniciar");
    start_button->setClickReaction(ShowDriversPage);
    start_button->setParent(quit_button);
    start_button->setRelativeX(quit_button->getWidth() + 5);
    start_button->setRelativeY(0);

    // // DRIVERS PAGE
    Driver * tmp_driver = new Driver("Joaquim Teixeira", 62, "Scania 113h");
    DriverInfoCard * tmp_dic = DriverInfoCard::newDriverInfoCard(tmp_driver, 300, 100);
    drivers.push_back({tmp_driver, tmp_dic});

    drivers_menu_current_page = DynamicText::newDynamicText("Pag. 0");
    drivers_menu_next_page = Button::newButton("Proxima Pag.");
    drivers_menu_next_page->setClickReaction(NextPageDriversMenu);

    drivers_menu_previous_page = Button::newButton("Pag. Anterior");
    drivers_menu_previous_page->setClickReaction(PreviousPageDriversMenu);
    
    drivers_menu = PageContainer::newPageContainer(Assets::WINDOW_WIDTH, Assets::WINDOW_HEIGHT - Assets::BUTTON_HEIGHT - 10, 3);
    for (auto driver : drivers)
        drivers_menu->pushItem(driver.second);
    
    drivers_menu_current_page->setParent(drivers_menu);
    drivers_menu_current_page->setRelativeX(drivers_menu->getWidth() / 2 - drivers_menu_current_page->getWidth() / 2);
    drivers_menu_current_page->setRelativeY(drivers_menu->getHeight() + Assets::BUTTON_HEIGHT / 2 - drivers_menu_current_page->getHeight() / 2);

    drivers_menu_previous_page->setParent(drivers_menu);
    drivers_menu_previous_page->setRelativeX(drivers_menu_current_page->getRelativeX() - drivers_menu_previous_page->getWidth() - 10);
    drivers_menu_previous_page->setRelativeY(drivers_menu->getHeight() + 5);

    drivers_menu_next_page->setParent(drivers_menu);
    drivers_menu_next_page->setRelativeX(drivers_menu_current_page->getRelativeX() + drivers_menu_current_page->getWidth() + 10);
    drivers_menu_next_page->setRelativeY(drivers_menu->getHeight() + 5);

    drivers_menu_previous_page->hide();
    drivers_menu_previous_page->deactivate();
    drivers_menu_current_page->hide();
    drivers_menu_next_page->hide();
    drivers_menu_next_page->deactivate();
    drivers_menu->hide();

    create_driver = Button::newButton("Novo motorista");
    create_driver->setRelativeX(Assets::WINDOW_WIDTH - create_driver->getWidth() - 10);
    create_driver->setRelativeY(Assets::WINDOW_HEIGHT - create_driver->getHeight() - 10);
    create_driver->setClickReaction(CreateDriver);
    create_driver->hide();
    create_driver->deactivate();

    see_deliveries = Button::newButton("Ver entregas");
    see_deliveries->setParent(create_driver);
    see_deliveries->setRelativeX(0);
    see_deliveries->setRelativeY(-create_driver->getHeight() - 10);
    see_deliveries->setClickReaction(ShowDeliveries);
    see_deliveries->hide();
    see_deliveries->deactivate();

    // DRIVER UPDATE PAGE
    new_driver_name = SolidText::newSolidText("Nome:");
    new_driver_name->setRelativeX(Assets::WINDOW_WIDTH / 2 - new_driver_name->getWidth() / 2);
    new_driver_name->setRelativeY(10);
    new_driver_name_field = TextField::newTextField();
    new_driver_name_field->setParent(new_driver_name);
    new_driver_name_field->setRelativeX(0);
    new_driver_name_field->setRelativeY(new_driver_name->getHeight() + 3);

    new_driver_age = SolidText::newSolidText("Idade:");
    new_driver_age->setParent(new_driver_name_field);
    new_driver_age->setRelativeX(0);
    new_driver_age->setRelativeY(new_driver_name_field->getHeight() + 10);
    new_driver_age_field = TextField::newTextField();
    new_driver_age_field->setParent(new_driver_age);
    new_driver_age_field->setRelativeX(0);
    new_driver_age_field->setRelativeY(new_driver_age->getHeight() + 3);
    new_driver_age_field->setNumericOnlyMode();

    new_driver_vehicle = SolidText::newSolidText("Veiculo:");
    new_driver_vehicle->setParent(new_driver_age_field);
    new_driver_vehicle->setRelativeX(0);
    new_driver_vehicle->setRelativeY(new_driver_age_field->getHeight() + 10);
    new_driver_vehicle_field = TextField::newTextField();
    new_driver_vehicle_field->setParent(new_driver_vehicle);
    new_driver_vehicle_field->setRelativeX(0);
    new_driver_vehicle_field->setRelativeY(new_driver_vehicle->getHeight() + 3);
    
    new_driver_confirm = Button::newButton("Confirmar");
    new_driver_confirm->setRelativeX(Assets::WINDOW_WIDTH / 2 - new_driver_confirm->getWidth() / 2);
    new_driver_confirm->setRelativeY(Assets::WINDOW_HEIGHT - new_driver_confirm->getHeight() - 10);
    new_driver_confirm->setClickReaction(ConfirmDriver);
    HideDriverUpdateElements();

    srand(NULL);
    for (int i = 0; i < 25; i++) {
        int64_t initial_secs = rand() % 82800;
        int64_t final_secs = rand()%(86400-initial_secs + 1) + initial_secs;
        Delivery * delivery = new Delivery("Entrega " + std::to_string(i+1), Time(initial_secs), Time(final_secs), rand() % 501);
        deliveries.push_back({delivery, DeliveryInfoCard::newDeliveryInfoCard(delivery, 300, 100)});
    }

    planning_button = Button::newButton("Planejamento");
    planning_button->setGlobalX(Assets::WINDOW_WIDTH - planning_button->getWidth() - 10);
    planning_button->setGlobalY(Assets::WINDOW_HEIGHT - planning_button->getHeight() - 10);
    planning_button->setClickReaction(ShowPlanning);
    planning_button->hide();
    planning_button->deactivate();

    deliveries_menu = SliderContainer::newSliderContainer(Assets::WINDOW_WIDTH, 300, 100);
    for (auto delivery : deliveries)
        deliveries_menu->pushItem(delivery.second);
    deliveries_menu->hide();

    planning_button->setParent(deliveries_menu);
}