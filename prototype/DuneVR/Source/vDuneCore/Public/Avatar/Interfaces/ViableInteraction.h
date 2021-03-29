// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ViableInteraction.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UViableInteraction : public UObject
{
	GENERATED_BODY()

	UViableInteraction();

	UPROPERTY(VisibleAnywhere)
	class ADuneAvatar * avatar_;

    UPROPERTY(VisibleAnywhere)
	class APalpableActor * palpable_object_;

    UFUNCTION(BlueprintCallable, Category=Interfaces)
    FString generate_user_instruction();

    bool is_active_;

public:
    void initialize(class ADuneAvatar * avatar, class APalpableActor * object);

	bool is_viable();

	void commit();
};


