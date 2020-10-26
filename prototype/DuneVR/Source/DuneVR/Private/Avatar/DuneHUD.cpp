// Fill out your copyright notice in the Description page of Project Settings.


#include "DuneHUD.h"
#include "DuneAvatar.h"
#include "DuneController.h"
#include "Blueprint/UserWidget.h"

void ADuneHUD::BeginPlay()
{
    Super::BeginPlay();
}

void ADuneHUD::DrawHUD()
{

}

UUserWidget * ADuneHUD::update_hud_widget()
{
    UUserWidget * widget = nullptr;

    UE_LOG(LogClass, Log, TEXT("Updating HUD widget. . ."));
    auto avatar = Cast<ADuneAvatar>(GetOwningPawn());

    if (avatar)
    {
        const auto mode = avatar->get_avatar_mode();
        auto controller = avatar->GetController<ADuneController>();

        TSubclassOf<class UUserWidget> hud_type;

        if (mode)
        {
            hud_type = mode->get_hud_type();

            if(hud_type)
            {
                if (controller)
                    widget = controller->new_widget(*hud_type);

                if (widget)
                {
                    this->remove_widgets();
                    widget->AddToViewport();
                }
            }
        }
        else
        {
            this->remove_widgets();
        }
    }

    return widget;
}

void ADuneHUD::remove_widgets()
{
    if (GEngine && GEngine->GameViewport)
    {
        GEngine->GameViewport->RemoveAllViewportWidgets();
    }
}