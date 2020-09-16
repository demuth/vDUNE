// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ViableInteraction.generated.h"

/**
 * 
 */
UCLASS()
class UViableInteraction : public UObject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class APawn * pawn_;

    UPROPERTY(VisibleAnywhere)
	class APalpableActor * palpable_object_;

public:
    void initialize(class APawn * pawn, class APalpableActor * object);

	bool is_viable();

	void commit();
};
