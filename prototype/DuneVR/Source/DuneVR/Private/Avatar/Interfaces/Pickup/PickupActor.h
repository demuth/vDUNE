// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PalpableActor.h"
#include "PickupActor.generated.h"

UCLASS()
class APickupActor : public APalpableActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
    APickupActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pickup)
    FString name_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pickup)
    FString details_;

    class UPickupModel * on_pickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual bool actor_interaction_viable(const ADuneAvatar * const avatar) const override;

    virtual void interact(class ADuneAvatar * const avatar, class UViableInteraction * interaction, bool &is_active) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Pickup, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* mesh_;

    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Pickup, meta = (AllowPrivateAccess = "true"))
    class UPickupModel * pickup_data_;
};
