// Fill out your copyright notice in the Description page of Project Settings.


#include "vDuneCore/Public/Avatar/Interfaces/Observable/ObjectViewer.h"
#include "vDuneCore/Public/Avatar/Interfaces/Observable/ObservableActor.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AObjectViewer::AObjectViewer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a camera boom (pulls in towards the player if there is a collision)
    camera_boom_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    camera_boom_->SetupAttachment(RootComponent);
    camera_boom_->TargetArmLength = 80.0f;
    camera_boom_->bUsePawnControlRotation = true;
    camera_boom_->ProbeChannel = ECollisionChannel::ECC_EngineTraceChannel1;

    // Create a viewer camera
    viewer_camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewerCamera"));
    viewer_camera_->SetupAttachment(camera_boom_, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    viewer_camera_->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void AObjectViewer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AObjectViewer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AObjectViewer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AObjectViewer::try_end_viewer_session()
{
    /// Execute the delegate.
    UE_LOG(LogClass, Log, TEXT("%s is trying to initiate an interaction. "), *this->GetName());
    delegate_.ExecuteIfBound();
}

void AObjectViewer::update_spring_arm_location(FVector location, FRotator rotator)
{
    if (camera_boom_)
    {
        camera_boom_->SetWorldLocation(location);
        camera_boom_->SetWorldRotation(rotator);
    }
}

void AObjectViewer::set_distance(float distance)
{
    camera_boom_->TargetArmLength = distance;
}

void AObjectViewer::bind_delegate(AObservableActor * actor, void (AObservableActor::*fptr)())
{
    delegate_.BindUObject(actor, fptr);
}