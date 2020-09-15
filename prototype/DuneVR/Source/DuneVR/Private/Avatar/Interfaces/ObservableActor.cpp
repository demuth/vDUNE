// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservableActor.h"

// Sets default values
AObservableActor::AObservableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObservableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObservableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

