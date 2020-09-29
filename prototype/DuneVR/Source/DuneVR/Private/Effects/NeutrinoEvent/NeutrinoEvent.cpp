// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutrinoEvent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ANeutrinoEvent::ANeutrinoEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>( TEXT("RootComponent") );
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius( 40.0f );

    for (int i=0; i < 100; ++i)
    {
        USphereComponent* sphere = CreateDefaultSubobject<USphereComponent>( *FString::Printf( TEXT("sphere-%i"), i ) );
        sphere->SetRelativeLocation(FVector(i * 7, i * 13, i * 10));
        sphere->InitSphereRadius( i/5 );
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

