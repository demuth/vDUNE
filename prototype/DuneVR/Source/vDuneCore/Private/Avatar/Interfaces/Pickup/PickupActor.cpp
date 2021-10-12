// Fill out your copyright notice in the Description page of Project Settings.


#include "vDuneCore/Public/Avatar/Interfaces/Pickup/PickupActor.h"
#include "vDuneCore/Public/Avatar/Interfaces/Pickup/PickupModel.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "vDuneCore/Public/Avatar/Interfaces/ViableInteraction.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APickupActor::APickupActor()
: APalpableActor()
{
	PrimaryActorTick.bCanEverTick = false;

    UCapsuleComponent* interaction_bounds = CreateDefaultSubobject<UCapsuleComponent>( TEXT("EventBounds") );
    interaction_bounds->InitCapsuleSize(interaction_radius_, 100.0f);
    RootComponent = interaction_bounds;

	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pickup_mesh"));
    RootComponent = mesh_;
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	//Generates data about the collectible.
	pickup_data_ = NewObject<UPickupModel>();
	pickup_data_->Initialize(name_, details_);
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPickupModel * APickupActor::on_pickup()
{
    FString name = GetName();
    UE_LOG(LogClass, Log, TEXT("Collected %s"), *name);

    this->Destroy();

    return pickup_data_;
}

bool APickupActor::actor_interaction_viable(const ADuneAvatar * const avatar) const
{
    if (!avatar)
        return false;

    FVector point1 = this->GetActorLocation();
    FVector point2 = avatar->GetActorLocation();

    FVector displacement3D = point2 - point1;
    FVector2D displacement = FVector2D(displacement3D.X, displacement3D.Y);

    return (displacement.Size() < interaction_radius_);// recorded in centimeters.
}

void APickupActor::interact(ADuneAvatar * const avatar, UViableInteraction * interaction, bool &is_active)
{
    if (avatar)
    {
        auto data = this->on_pickup();

        avatar->add_collectible(data);

        is_active = false;
    }
    else
    {
        is_active = false;
    }
}

