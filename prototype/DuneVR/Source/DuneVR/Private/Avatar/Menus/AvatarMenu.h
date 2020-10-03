// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/AvatarMode.h"
#include "AvatarMenu.generated.h"

/**
 * 
 */
UCLASS()
class UAvatarMenu : public UAvatarMode
{
	GENERATED_BODY()

    virtual void setup(class APawn * pawn, FTimerManager *manager) override;
    virtual void teardown() override;
	
};
