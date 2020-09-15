// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PalpableActor.h"
#include "PickupActor.generated.h"

UCLASS()
class APickupActor : public APalpableActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
    APickupActor();

    UFUNCTION(BlueprintPure, Category=pickup)
    bool is_active() const;

    UFUNCTION(BlueprintCallable, Category=pickup)
    void set_state(bool pickup_is_active);

    void on_pickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//true when the pickup is available false when it has been picked up.
	bool is_active_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Pickup, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* mesh_;
};
