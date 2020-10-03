// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DuneController.generated.h"

/**
 * 
 */
UCLASS()
class ADuneController : public APlayerController
{
	GENERATED_BODY()

public:
    ADuneController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widgets)
	TSubclassOf<class UUserWidget> collectibles_widget_;

    virtual void BeginPlay() override;

    void update_hud();

    UUserWidget * new_widget(TSubclassOf<class UUserWidget> type);

protected:
    virtual void SetupInputComponent() override;

    void toggle_collectibles_display();

    UFUNCTION(BlueprintCallable, Category=menus)
    void close_menu();

private:
    UUserWidget* w_collectibles_widget_;
    bool is_showing_collectibles_;

    void on_interaction_command();
    void remove_menus();
};
