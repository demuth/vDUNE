// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarMenu.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

UAvatarMenu::UAvatarMenu()
{
    mode_type_ = EAvatarMode::Menu;
}


UAvatarMenu::~UAvatarMenu()
{

}

void UAvatarMenu::setup(APawn * pawn, FTimerManager *manager)
{
    UAvatarMode::setup(pawn, manager);

    if (pawn_ != nullptr)
    {
        APlayerController * controller = Cast<APlayerController>(pawn_->GetController());

        if (controller != nullptr)
        {
            if(controller->SetPause(true))
                controller->bShowMouseCursor = true;

            else
                UE_LOG(LogClass, Error, TEXT("Failed to pause."));
        }
        else
        {
            UE_LOG(LogClass, Error, TEXT("Failed to setup menu: Could not find controller."));
        }
    }
    else
    {
        UE_LOG(LogClass, Error, TEXT("Failed to setup menu: Could not find pawn."));
    }
}

void UAvatarMenu::teardown()
{
    UAvatarMode::teardown();

    if (pawn_ != nullptr)
    {
        APlayerController * controller = Cast<APlayerController>(pawn_->GetController());

        if (controller != nullptr)
        {
            if(controller->SetPause(false))
                controller->bShowMouseCursor = false;

            else
                UE_LOG(LogClass, Error, TEXT("Failed to unpause."));
        }
        else
        {
            UE_LOG(LogClass, Error, TEXT("Failed to tear down menu: Could not find controller."));
        }
    }
    else
    {
        UE_LOG(LogClass, Error, TEXT("Failed to tear down menu:  Could not find pawn."));
    }
}