#include "Neutrino/NeutrinoPoint.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANeutrinoPoint::ANeutrinoPoint()
{
	PrimaryActorTick.bCanEverTick = true;

    mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pickup_mesh"));
    RootComponent = mesh_;
}

// Called when the game starts or when spawned
void ANeutrinoPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANeutrinoPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

