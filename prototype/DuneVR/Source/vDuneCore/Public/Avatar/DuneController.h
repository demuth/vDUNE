// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DuneController.generated.h"

/**
 * 
 */
UCLASS()
class VDUNECORE_API ADuneController : public APlayerController
{
	GENERATED_BODY()

public:
    ADuneController();

    virtual void BeginPlay() override;

    UUserWidget * update_hud();

    UUserWidget * new_widget(TSubclassOf<class UUserWidget> type);

    int32 add_binding(FInputActionBinding binding);
    void remove_binding(int32 handle);

protected:
    virtual void SetupInputComponent() override;

    UFUNCTION(BlueprintCallable, Category=menus)
    void close_menu();

private:
    void toggle_collectibles_display();
    void toggle_server_menu();
    void on_interaction_command();
};
