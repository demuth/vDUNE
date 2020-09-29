// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NeutrinoEvent.generated.h"

UCLASS()
class ANeutrinoEvent : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ANeutrinoEvent();

    TArray<class USphereComponent*> component_list_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
