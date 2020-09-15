// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"

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

void APickupActor::on_pickup()
{
    FString name = GetName();
    UE_LOG(LogClass, Log, TEXT("Collected %s"), *name);
}

