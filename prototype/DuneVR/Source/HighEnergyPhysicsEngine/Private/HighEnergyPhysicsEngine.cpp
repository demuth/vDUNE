// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "../Public/HighEnergyPhysicsEngine.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FHighEnergyPhysicsEngine, HighEnergyPhysicsEngine);


void FHighEnergyPhysicsEngine::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("*** NEUTRINO ENGINE STARTUP ***"));
}


void FHighEnergyPhysicsEngine::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("*** NEUTRINO ENGINE SHUTDOWN ***"));
}