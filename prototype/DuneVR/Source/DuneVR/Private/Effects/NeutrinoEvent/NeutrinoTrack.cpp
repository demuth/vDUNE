#include "NeutrinoTrack.h"
#include "NeutrinoEvent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "JsonObjectConverter.h"
#include <cmath>

#include "NeutrinoEventStruct.h"

ANeutrinoTrack::ANeutrinoTrack()
{
    PrimaryActorTick.bCanEverTick = true;

    sphere_ = CreateDefaultSubobject<USphereComponent>( TEXT("RootComponent") );
    RootComponent = sphere_;
    sphere_->InitSphereRadius( 40.0f );
}

void ANeutrinoTrack::BeginPlay()
{
    Super::BeginPlay();
}

void ANeutrinoTrack::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ANeutrinoTrack::add_bounds(FVector location, FVector size)
{
    UBoxComponent* event_bounds = NewObject<UBoxComponent>( this );
    event_bounds->SetRelativeLocation(FVector(location.X, location.Y, location.Z));
    event_bounds->InitBoxExtent(FVector(size.X/2, size.Y/2, size.Z/2));
    event_bounds->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    event_bounds->RegisterComponent();
}

void ANeutrinoTrack::add_points(TArray<FNeutrinoPointData> points)
{
    int i = 0;
    for(auto &point : points)
    {
        USphereComponent *sphere = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), *FString::Printf(TEXT("sphere-%i"), i));
        sphere->SetRelativeLocation(FVector(point.X, point.Y, point.Z));
        sphere->InitSphereRadius(point.Charge * 0.001);
        component_list_.Add(sphere);
        sphere->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        sphere->RegisterComponent();
        i++;
    }
};