// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectViewer.h"
#include "../../DuneAvatar.h"
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
    camera_boom_->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
    camera_boom_->bUsePawnControlRotation = true; // Rotate the arm based on the controller

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

