// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PalpableActor.generated.h"

UCLASS()
class APalpableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APalpableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pickup)
    float interaction_radius_ = 100.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool actor_interaction_viable(const AActor * const actor) const;

    virtual void interact(class ADuneAvatar * const actor);
};
