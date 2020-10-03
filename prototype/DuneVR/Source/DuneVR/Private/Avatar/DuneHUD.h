// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DuneHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADuneHUD : public AHUD
{
	GENERATED_BODY()

public:
    void update_hud_widget();

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	void remove_widgets();
    FTimerHandle timer_handle_;
};
