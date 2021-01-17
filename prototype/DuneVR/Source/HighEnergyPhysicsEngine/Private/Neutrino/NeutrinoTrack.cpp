#include "../../Public/Neutrino/NeutrinoTrack.h"
#include "../../Public/Neutrino/NeutrinoEvent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "JsonObjectConverter.h"
#include <cmath>

#include "NeutrinoEventStruct.h"

ANeutrinoTrack::ANeutrinoTrack()
{
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>( TEXT("RootComponent") );
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius( 40.0f );
}

void ANeutrinoTrack::BeginPlay()
{
    Super::BeginPlay();
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
    for(auto &point : points)
    {
        auto new_point = GetWorld()->SpawnActor<ANeutrinoPoint>(point_bp_.Get(), GetActorLocation(), GetActorRotation());
        new_point->SetActorRelativeLocation(FVector(point.X, point.Y, point.Z));
        new_point->SetActorScale3D(FVector(point.Charge * .00002));
        new_point->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
        point_list_.Add(new_point);
    }
};