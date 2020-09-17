// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Collectible.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UCollectible : public UObject
{
	GENERATED_BODY()

public:
    void Initialize(FString name, FString details);

	UPROPERTY(BlueprintReadonly, Category=Inventory)
	FString collectible_name;

	UPROPERTY(BlueprintReadonly, Category=Inventory)
	FString collectible_details;
};
