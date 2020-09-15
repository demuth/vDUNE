// Fill out your copyright notice in the Description page of Project Settings.


#include "DuneController.h"
#include "Blueprint/UserWidget.h"

ADuneController::ADuneController()
: is_showing_collectibles_(false)
{

}

void ADuneController::BeginPlay()
{
    Super::BeginPlay();

    this->remove_menus();
}

void ADuneController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Set up menu key bindings
    InputComponent->BindAction("ShowCollectibles", IE_Released, this, &ADuneController::toggle_collectibles_display);
}

void ADuneController::toggle_collectibles_display()
{
    UE_LOG(LogClass, Log, TEXT("toggle collectible screen"));
    if(collectibles_widget_)
    {
        w_collectibles_widget_ = CreateWidget<UUserWidget>(this, collectibles_widget_);

        if (w_collectibles_widget_)
        {
            if (!is_showing_collectibles_)
            {
                if (this->SetPause(true))
                {
                    w_collectibles_widget_->AddToViewport();
                    is_showing_collectibles_ = true;
                    bShowMouseCursor = true;
                }
                else
                {
                    UE_LOG(LogClass, Warning, TEXT("Failed to open collectibles."));
                }
            }
            else
            {
                this->close_menu();
            }
        }
    }
}

void ADuneController::remove_menus()
{
    if (GEngine && GEngine->GameViewport)
    {
        GEngine->GameViewport->RemoveAllViewportWidgets();
    }
}

void ADuneController::close_menu()
{
    if (this->SetPause(false))
    {
        this->remove_menus();
        is_showing_collectibles_ = false;
        bShowMouseCursor = false;
    }
    else
    {
        UE_LOG(LogClass, Warning, TEXT("Failed to leave collectibles."));
    }
}