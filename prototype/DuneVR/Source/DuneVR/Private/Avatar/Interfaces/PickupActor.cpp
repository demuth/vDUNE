// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Collectible.h"
#include "../DuneAvatar.h"

// Sets default values
APickupActor::APickupActor()
: is_active_(true)
{
	PrimaryActorTick.bCanEverTick = false;

	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pickup_mesh"));
    RootComponent = mesh_;
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	//Generates data about the collectible.
	collectible_data_ = NewObject<UCollectible>();
	collectible_data_->Initialize(name_, details_);
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickupActor::is_active() const
{
    return is_active_;
}

void APickupActor::set_state(bool pickup_is_active)
{
    is_active_ = pickup_is_active;
}

UCollectible * APickupActor::on_pickup()
{
    FString name = GetName();
    UE_LOG(LogClass, Log, TEXT("Collected %s"), *name);

    this->Destroy();

    return collectible_data_;
}

bool APickupActor::actor_interaction_viable(const AActor * const actor) const
{
    if (!actor)
        return false;

    FVector point1 = this->GetActorLocation();
    FVector point2 = actor->GetActorLocation();

    FVector displacement3D = point2 - point1;
    FVector2D displacement = FVector2D(displacement3D.X, displacement3D.Y);

    return (displacement.Size() < interaction_radius_);
}

void APickupActor::interact(ADuneAvatar * const avatar)
{
    if (avatar && avatar->add_collectible(this->on_pickup()))
        this->set_state(false);
}

