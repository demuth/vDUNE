// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DefaultGameMode.generated.h"

UENUM(BlueprintType)
enum class UDuneState : uint8
{
    Select,
    Active
};

/**
 *
 */
UCLASS()
class DUNEVR_API ADefaultGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADefaultGameMode(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category=State)
    UDuneState get_state();
};
