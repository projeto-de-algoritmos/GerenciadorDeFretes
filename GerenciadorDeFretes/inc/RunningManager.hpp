#ifndef _RUNNING_MANAGER_HPP_
#define _RUNNING_MANAGER_HPP_

#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include "Button.hpp"
#include "Helpers.hpp"
#include "InteractiveComponent.hpp"
#include "SolidImage.hpp"
#include "SolidText.hpp"
#include "VisualComponent.hpp"
#include "Timer.hpp"
#include "Assets.hpp"
#include "Checkbox.hpp"
#include "DynamicText.hpp"

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdint>
#include <vector>

namespace RunningManager
{
    // -----------------------------------------------------------
    // CORE FUNCTIONS
    void StartFrame();
    void FinishFrame();
    void HandleUserInput();
    void FinishProgramExecution();
    bool ProgramIsRunning();
    void StartDependencies();
    void SetVerboseMode();
    void ReleaseDependencies();
    void RenderScreen();
    
    // -----------------------------------------------------------
    // UI FUNCTIONS
    void InitializeUIElments();
}

#endif
