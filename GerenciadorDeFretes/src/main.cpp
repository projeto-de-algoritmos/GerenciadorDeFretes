#include "RunningManager.hpp"

int main()
{
    RunningManager::StartDependencies();
    //RunningManager::SetVerboseMode();
    RunningManager::InitializeUIElments();

    while (RunningManager::ProgramIsRunning()) {
        RunningManager::StartFrame();
        RunningManager::HandleUserInput();
        RunningManager::RenderScreen();
        RunningManager::FinishFrame();
    }

    RunningManager::ReleaseDependencies();
    return 0;
}
