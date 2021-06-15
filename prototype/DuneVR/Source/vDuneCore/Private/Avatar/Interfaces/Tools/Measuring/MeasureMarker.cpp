// Fill out your copyright notice in the Description page of Project Settings.


#include "MeasureMarker.h"
#include "Components/SphereComponent.h"

// Sets default values
AMeasureMarker::AMeasureMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>( TEXT("RootComponent") );
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius( 40.0f );
}

// Called when the game starts or when spawned
void AMeasureMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeasureMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

