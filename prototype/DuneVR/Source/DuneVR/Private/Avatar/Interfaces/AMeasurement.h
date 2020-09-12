// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMeasurement.generated.h"

UCLASS()
class AAMeasurement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMeasurement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Measurement")
	AActor* point_1_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Measurement")
	AActor* point_2_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Measurement")
    float measurement_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
