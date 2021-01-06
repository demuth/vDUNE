// Fill out your copyright notice in the Description page of Project Settings.


#include "NeutrinoEvent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "JsonObjectConverter.h"
#include <cmath>

#include "NeutrinoEventStruct.h"

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


    FString FilePath = "/Users/lucassorenson/Code/dune/Subversion/trunk/prototype/DuneVR/Content/information.json";
    FString FileData = "";
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("DID NOT FIND FILE"));
        return;
    }

    FNeutrinoEventList events;
    FFileHelper::LoadFileToString(FileData, *FilePath);

    UE_LOG(LogTemp, Warning, TEXT("%s"), *FileData);

    if (FJsonObjectConverter::JsonObjectStringToUStruct(FileData, &events, 0, 0))
    {
        UE_LOG(LogClass, Warning, TEXT("CONVERTED"));
        int i = 0;
        for(auto &track : events.EventList[4].Tracks)
        {
            for(auto &point : track.Points) {
                USphereComponent *sphere = CreateDefaultSubobject<USphereComponent>(
                        *FString::Printf(TEXT("sphere-%i"), i));
                sphere->SetRelativeLocation(FVector(point.X, point.Y, point.Z));
                sphere->InitSphereRadius(point.Charge * 0.001);
                component_list_.Add(sphere);
                sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
                i++;
            }
        }
    }
    else
    {
        UE_LOG(LogClass, Error, TEXT("Failed to convert!"));
    }
}

// Called when the game starts or when spawned
void ANeutrinoEvent::BeginPlay()
{
	Super::BeginPlay();

    FString FilePath = "/Users/lucassorenson/Code/dune/Subversion/trunk/prototype/DuneVR/Content/information.json";
    FString FileData = "";
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("DID NOT FIND FILE"));
        return;
    }

    FNeutrinoEventList events;
    FFileHelper::LoadFileToString(FileData, *FilePath);

    UE_LOG(LogTemp, Warning, TEXT("%s"), *FileData);

    if (FJsonObjectConverter::JsonObjectStringToUStruct(FileData, &events, 0, 0))
    {
        UE_LOG(LogClass, Warning, TEXT("CONVERTED"));
        for (auto &event : events.EventList)
        {
            UE_LOG(LogClass, Warning, TEXT("Event: %i Number of Tracks: %i"), event.Id, event.Tracks.Num());
        }

    }
    else
    {
        UE_LOG(LogClass, Error, TEXT("Failed to convert!"));
    }
}

// Called every frame
void ANeutrinoEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

