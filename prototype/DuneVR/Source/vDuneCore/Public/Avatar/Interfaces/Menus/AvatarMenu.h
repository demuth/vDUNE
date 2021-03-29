// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/Interfaces/Modes/AvatarMode.h"
#include "Avatar/Interfaces/Modes/EAvatarMode.h"
#include "AvatarMenu.generated.h"

/**
 * 
 */
UCLASS()
class VDUNECORE_API UAvatarMenu : public UAvatarMode
{
	GENERATED_BODY()

public:
    UAvatarMenu();
	~UAvatarMenu();

    virtual void setup(class APawn * pawn, FTimerManager *manager) override;
    virtual void teardown() override;
	
};
