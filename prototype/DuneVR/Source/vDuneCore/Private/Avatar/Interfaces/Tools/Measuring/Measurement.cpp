// Fill out your copyright notice in the Description page of Project Settings.


#include "Measurement.h"
#include "MeasureMarker.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMeasurement::AMeasurement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>( TEXT("RootComponent") );
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius( 40.0f );

    particle_system_ = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MeasurementDisplay"));
    particle_system_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMeasurement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeasurement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector point_1 = point_1_->GetActorLocation();
    FVector point_2 = point_2_->GetActorLocation();

    FVector distance = point_2 - point_1;

    measurement_ = distance.Size();
}

void AMeasurement::set_points(AMeasureMarker *marker1, AMeasureMarker *marker2, UParticleSystem * particle_system)
{
    if (marker1 == nullptr || marker2 == nullptr)
    {
        UE_LOG(LogClass, Log, TEXT("Parameters null."));
    }

    point_1_ = marker1;
    point_2_ = marker2;

    if (particle_system_ != nullptr)
    {
        particle_system_->SetTemplate(particle_system);

        particle_system_->SetActorParameter(TEXT("Start"), point_1_);
        particle_system_->SetActorParameter(TEXT("End"), point_2_);
    }

}

