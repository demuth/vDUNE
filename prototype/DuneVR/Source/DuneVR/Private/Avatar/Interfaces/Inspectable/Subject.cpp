// Fill out your copyright notice in the Description page of Project Settings.


#include "Subject.h"

// Sets default values
ASubject::ASubject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pickup_mesh"));
    RootComponent = mesh_;
}

// Called when the game starts or when spawned
void ASubject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASubject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ASubject::get_name() const
{
    return name_;
}
