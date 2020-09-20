// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutrinoEvent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ANeutrinoEvent::ANeutrinoEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	particle_system_ = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particle_system"));
	RootComponent = particle_system_;
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

