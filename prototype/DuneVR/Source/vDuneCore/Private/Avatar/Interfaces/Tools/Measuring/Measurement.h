// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Measurement.generated.h"

UCLASS()
class AMeasurement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeasurement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Measurement")
	AActor* point_1_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Measurement")
	AActor* point_2_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Measurement")
    float measurement_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Measurement")
	class UParticleSystemComponent * particle_system_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void set_points(class AMeasureMarker * marker1, class AMeasureMarker * marker2, UParticleSystem * particle_system);
};
