// Fill out your copyright notice in the Description page of Project Settings.


#include "Measurement.h"

// Sets default values
AMeasurement::AMeasurement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

    UE_LOG(LogTemp, Log, TEXT("Measurement: %f"), distance.Size());
    measurement_ = distance.Size();

}

