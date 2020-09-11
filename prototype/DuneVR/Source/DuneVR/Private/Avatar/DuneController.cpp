// Fill out your copyright notice in the Description page of Project Settings.


#include "DuneController.h"
#include "Blueprint/UserWidget.h"

void ADuneController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("begin play"));
    if(w_test_widget_)
    {
        UE_LOG(LogTemp, Warning, TEXT("widget exists"));
        test_widget_ = CreateWidget<UUserWidget>(this, w_test_widget_);

        if (test_widget_)
        {
            UE_LOG(LogTemp, Warning, TEXT("widget constructed"));
            test_widget_->AddToViewport();
        }
    }
}
