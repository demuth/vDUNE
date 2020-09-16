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

    UFUNCTION(BlueprintPure, Category=Pickup)
    bool is_active() const;

    UFUNCTION(BlueprintCallable, Category=Pickup)
    void set_state(bool pickup_is_active);

    class UCollectible * on_pickup();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pickup)
    FString name_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pickup)
    FString details_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual bool actor_interaction_viable(const AActor * const actor) const override;
    virtual void interact(class ADuneAvatar * const actor) override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Pickup, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* mesh_;

    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Pickup, meta = (AllowPrivateAccess = "true"))
    class UCollectible * collectible_data_;

    //true when the pickup is available false when it has been picked up.
    bool is_active_;
};
