// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DuneAvatar.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/PickupActor.h"
#include "Interfaces/Collectible.h"
#include "Interfaces/ViableInteraction.h"

//////////////////////////////////////////////////////////////////////////
// ADuneAvatar

ADuneAvatar::ADuneAvatar()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	collection_sphere_ = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	collection_sphere_->AttachTo(RootComponent);
	collection_sphere_->SetSphereRadius(200.0f);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADuneAvatar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADuneAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADuneAvatar::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADuneAvatar::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADuneAvatar::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADuneAvatar::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADuneAvatar::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADuneAvatar::OnResetVR);

	// Interaction bindings
    PlayerInputComponent->BindAction("Interact", IE_Released, this, &ADuneAvatar::pickup);
}

void ADuneAvatar::Tick(float delta_seconds)
{
    detect_viable_interactions();

    update_viable_interactions();
}

void ADuneAvatar::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADuneAvatar::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ADuneAvatar::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ADuneAvatar::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADuneAvatar::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADuneAvatar::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADuneAvatar::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ADuneAvatar::detect_viable_interactions()
{
    TArray<AActor*> collected_actors;
    GetCollectionSphere()->GetOverlappingActors(collected_actors);

    for (int32 i = 0; i < collected_actors.Num(); ++i)
    {
        APickupActor* const pickup_candidate = Cast<APickupActor>(collected_actors[i]);

        //Executed on active pickups in the sphere of influence.
        if (pickup_candidate && !pickup_candidate->IsPendingKill() && pickup_candidate->is_active())
        {
            if (pickup_candidate->actor_interaction_viable(this))
            {
                auto viable_interaction = NewObject<UViableInteraction>();
                viable_interaction->initialize(this, pickup_candidate);
                viable_interactions_.Add(pickup_candidate->GetName(), viable_interaction);
            }
        }
    }
}

void ADuneAvatar::update_viable_interactions()
{
    for (auto itr = viable_interactions_.CreateConstIterator(); itr; ++itr)
    {
        //if interactions are no longer viable remove them.
        if (!itr.Value()->is_viable())
            viable_interactions_.Remove(itr.Key());
    }
}

void ADuneAvatar::pickup()
{
    for (auto itr = viable_interactions_.CreateConstIterator(); itr; ++itr)
    {
        auto interaction = itr.Value();

        if (interaction)
        {
            interaction->commit();
            viable_interactions_.Remove(itr.Key());
        }
        else
        {
            UE_LOG(LogClass, Error, TEXT("No viable interaction found for the object: %s"), *itr.Key());
        }
    }
}

TArray<UCollectible*> ADuneAvatar::get_collectibles()
{
    return collectibles_;
}

bool ADuneAvatar::add_collectible(UCollectible * collectible_data)
{
    if (collectible_data != nullptr)
    {
        UE_LOG(LogClass, Log, TEXT("Player collected: %s"), *collectible_data->collectible_name);
        collectibles_.Add(collectible_data);
        return true;
    }
    else
    {
        UE_LOG(LogClass, Warning, TEXT("Collectible returned null data."));
        return false;
    }
}