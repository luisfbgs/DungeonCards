#pragma once

#include "StageState.h"

class Stages {
public:
    static void InitStage1(); 
    static void InitStage2();
    static void CreatePlayers(std::shared_ptr<StageState> newStage);
};