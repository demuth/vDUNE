// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutrinoEvent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include <cmath>

// Sets default values
ANeutrinoEvent::ANeutrinoEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>( TEXT("RootComponent") );
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius( 40.0f );

    UBoxComponent* event_bounds = CreateDefaultSubobject<UBoxComponent>( TEXT("EventBounds") );
    event_bounds->InitBoxExtent(FVector(100, 100, 100));
    event_bounds->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    auto extent = event_bounds->GetScaledBoxExtent();
    auto relative_origin = extent * -1;
    int num_increments = (int)round(extent.Size());

    for (int i=0; i < num_increments; ++i)
    {
        float radius = 1 + FMath::Sin(((float)1 / (float)(num_increments / M_PI)) * i) * 7;
        float sin_position_offset = FMath::Sin(((float)1 / (float)(num_increments / (M_PI * 2))) * i) * 15;
        FVector xz_offset_vector = FVector(sin_position_offset, sin_position_offset, -1 * sin_position_offset);
        auto incremental_displacement = (extent * 2) / num_increments;
        FVector sphere_relative_location = (i * incremental_displacement) + relative_origin;

        USphereComponent* sphere = CreateDefaultSubobject<USphereComponent>( *FString::Printf( TEXT("sphere-%i"), i ) );
        sphere->SetRelativeLocation(sphere_relative_location + xz_offset_vector);
        sphere->InitSphereRadius( radius );
        component_list_.Add(sphere);
        sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    }
}

// Called when the game starts or when spawned
void ANeutrinoEvent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANeutrinoEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

