// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "../Public/vDuneCore.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FvDuneCore, vDuneCore);


void FvDuneCore::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("*** vDuneCore STARTUP ***"));
}


void FvDuneCore::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("*** vDuneCore SHUTDOWN ***"));
}