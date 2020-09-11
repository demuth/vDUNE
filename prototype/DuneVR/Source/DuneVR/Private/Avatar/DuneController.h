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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widgets)
	TSubclassOf<class UUserWidget> w_test_widget_;

	UUserWidget* test_widget_;

    virtual void BeginPlay() override;
};
