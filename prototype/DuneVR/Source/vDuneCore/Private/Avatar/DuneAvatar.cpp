#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "vDuneCore/Public/Avatar/DuneController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "vDuneCore/Public/Avatar/Interfaces/Pickup/PickupActor.h"
#include "vDuneCore/Public/Avatar/Interfaces/Pickup/PickupModel.h"
#include "vDuneCore/Public/Avatar/Interfaces/Observable/ObservableActor.h"
#include "vDuneCore/Public/Avatar/Interfaces/ViableInteraction.h"
#include "vDuneCore/Public/Avatar/Interfaces/Tools/AvatarTool.h"
#include "vDuneCore/Public/Avatar/Interfaces/Tools/MeasureTool.h"
#include "vDuneCore/Public/Avatar/Interfaces/Menus/AvatarMenu.h"
#include "vDuneCore/Public/Decorator/UserName.h"
#include "Blueprint/UserWidget.h"

//////////////////////////////////////////////////////////////////////////
// ADuneAvatar

ADuneAvatar::ADuneAvatar(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, DecoratorBase()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	base_turn_rate_ = 45.f;
    base_lookup_rate_ = 45.f;

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
	camera_boom_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	camera_boom_->SetupAttachment(RootComponent);
    camera_boom_->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
	camera_boom_->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	follow_camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	follow_camera_->SetupAttachment(camera_boom_, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	follow_camera_->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	collection_sphere_ = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	collection_sphere_->AttachTo(RootComponent);
	collection_sphere_->SetSphereRadius(200.0f);

    available_tool_.Add(EAvatarTool::None, nullptr);
	available_tool_.Add(EAvatarTool::MeasureTool, nullptr);
	available_tool_.Add(EAvatarTool::InspectTool, nullptr);

    available_mode_.Add(EAvatarMode::Roam, nullptr);
    available_mode_.Add(EAvatarMode::Menu, nullptr);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	DecoratorBase::set_decorator_name("Avatar");
	DecoratorBase::add_decorator<UserName>();
}

void ADuneAvatar::BeginPlay()
{
    Super::BeginPlay();


}

//////////////////////////////////////////////////////////////////////////
// Input

void ADuneAvatar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADuneAvatar::move_forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADuneAvatar::move_right);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADuneAvatar::turn_at_rate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADuneAvatar::look_up_at_rate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADuneAvatar::touch_started);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADuneAvatar::touch_stopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADuneAvatar::OnResetVR);

    FInputActionBinding MeasureModeBinding( "MeasureMode", IE_Released );
    MeasureModeBinding.ActionDelegate.GetDelegateForManualSet().BindLambda( [this]()
    {
        this->set_measure_mode();
    });
    PlayerInputComponent->AddActionBinding(MeasureModeBinding);

    FInputActionBinding PlaceMarkerBinding( "MeasurePlace", IE_Released );
    PlaceMarkerBinding.ActionDelegate.GetDelegateForManualSet().BindLambda( [this]()
    {
        //if the mode is the measure tool.
        UMeasureTool * measure_tool = Cast<UMeasureTool>(mode_);

        if (measure_tool)
            measure_tool->add_marker();

        else
            UE_LOG(LogClass, Warning, TEXT("The measure tool is either not active or it has been destroyed."));
    });
    PlayerInputComponent->AddActionBinding(PlaceMarkerBinding);

    FInputActionBinding InspectModeBinding( "InspectMode", IE_Released );
    InspectModeBinding.ActionDelegate.GetDelegateForManualSet().BindLambda( [this]()
    {
        this->set_inspect_mode();
    });

    PlayerInputComponent->AddActionBinding(InspectModeBinding);
}

void ADuneAvatar::Tick(float delta_seconds)
{
    DecoratorBase::update(delta_seconds);

    camera_boom_->SetWorldLocation((mode_ != nullptr) ? mode_->calculate_camera_displacement(this->get_follow_camera()->GetForwardVector(), this->GetActorLocation()) : this->GetActorLocation());
    camera_boom_->TargetArmLength = (mode_ != nullptr) ? mode_->calculate_camera_arm_length() : 300.0f;

    detect_viable_interactions();

    update_viable_interactions();
}

void ADuneAvatar::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADuneAvatar::touch_started(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ADuneAvatar::touch_stopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ADuneAvatar::turn_at_rate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * base_turn_rate_ * GetWorld()->GetDeltaSeconds());
}

void ADuneAvatar::look_up_at_rate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * base_lookup_rate_ * GetWorld()->GetDeltaSeconds());
}

void ADuneAvatar::move_forward(float Value)
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

void ADuneAvatar::move_right(float Value)
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
    get_collection_sphere()->GetOverlappingActors(collected_actors);

    for (int32 i = 0; i < collected_actors.Num(); ++i)
    {
        APickupActor* const pickup_candidate = Cast<APickupActor>(collected_actors[i]);

        //Executed on active pickups in the sphere of influence.
        if (pickup_candidate && !pickup_candidate->IsPendingKill())
        {
            if (pickup_candidate->actor_interaction_viable(this)  && !viable_interactions_.Find(pickup_candidate->GetName()))
            {
                auto viable_interaction = NewObject<UViableInteraction>();
                viable_interaction->initialize(this, pickup_candidate);
                viable_interactions_.Add(pickup_candidate->GetName(), viable_interaction);
            }
        }

        AObservableActor* const observable_candidate = Cast<AObservableActor>(collected_actors[i]);

        //Executed on active pickups in the sphere of influence.
        if (observable_candidate && !observable_candidate->IsPendingKill())
        {
            if (observable_candidate->actor_interaction_viable(this) && !viable_interactions_.Find(observable_candidate->GetName()))
            {
                auto viable_interaction = NewObject<UViableInteraction>();
                viable_interaction->initialize(this, observable_candidate);
                viable_interactions_.Add(observable_candidate->GetName(), viable_interaction);
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

void ADuneAvatar::try_interaction()
{
    UE_LOG(LogClass, Log, TEXT("%s is trying to initiate an interaction. "), *this->GetName());

    for (auto itr = viable_interactions_.CreateConstIterator(); itr; ++itr)
    {
        auto interaction = itr.Value();

        if (interaction)
        {
            interaction->commit();
        }
        else
        {
            UE_LOG(LogClass, Error, TEXT("No viable interaction found for the object: %s"), *itr.Key());
        }
    }
}

TArray<UPickupModel*> ADuneAvatar::get_collectibles() const
{
    return collectibles_;
}

UUserWidget * ADuneAvatar::display_pickup(TSubclassOf<UAvatarMenu> menu_type)
{
    UE_LOG(LogClass, Log, TEXT("display pickup called"));

    UUserWidget * widget = nullptr;
    auto controller = this->GetController<ADuneController>();

    //tear down any existing mode.
    if (mode_ != nullptr)
    {
        mode_->teardown();
    }

    if (!menu_type)
    {
        UE_LOG(LogClass, Error, TEXT("Tool class was not found. "));
        mode_ = nullptr;
    }
    else
    {
        UE_LOG(LogClass, Log, TEXT("Tool class was found. "));

        //assign a new mode instance and set it up.
        if (controller != nullptr)
        {
            auto menu = NewObject<UAvatarMenu>(this, menu_type);
            mode_ = menu;
            widget = controller->update_hud();

            //mode_ was reassigned therefore check that it is still valid.
            if (mode_ != nullptr)
            {
                UE_LOG(LogClass, Log, TEXT("Setup new mode."));
                mode_->setup( this, &GetWorldTimerManager() );
            }
            else
            {
                UE_LOG(LogClass, Error, TEXT("Mode reference was not valid. "));
            }
        }
        else
        {
            UE_LOG(LogClass, Error, TEXT("Controller reference was not valid. "));
        }

        return widget;
    }

    return nullptr;
}

TMap<FString, class UViableInteraction *> ADuneAvatar::get_viable_interactions() const
{
    return viable_interactions_;
}

bool ADuneAvatar::add_collectible(UPickupModel * collectible_data)
{
    if (collectible_data != nullptr)
    {
        UE_LOG(LogClass, Log, TEXT("Player collected: %s"), *collectible_data->get_name());
        collectibles_.Add(collectible_data);
        return true;
    }
    else
    {
        UE_LOG(LogClass, Warning, TEXT("Collectible returned null data."));
        return false;
    }
}

void ADuneAvatar::set_inspect_mode()
{
    auto tool = Cast<UAvatarTool>(mode_);

    if (!tool || tool->get_tool_type() != EAvatarTool::InspectTool)
    {
        this->use_tool(EAvatarTool::InspectTool);
    }
    else
    {
        this->set_mode(EAvatarMode::Roam);
    }

}

void ADuneAvatar::set_measure_mode()
{
    auto tool = Cast<UAvatarTool>(mode_);

    if (!tool || tool->get_tool_type() != EAvatarTool::MeasureTool)
    {
        this->use_tool(EAvatarTool::MeasureTool);
    }
    else
    {
        this->set_mode(EAvatarMode::Roam);
    }

}

void ADuneAvatar::use_tool(EAvatarTool tool)
{
    TSubclassOf<UAvatarMode>*  type = available_tool_.Find(tool);
    this->set_user_mode(type);
}

void ADuneAvatar::set_mode(EAvatarMode mode)
{
    TSubclassOf<UAvatarMode>* type = available_mode_.Find(mode);
    this->set_user_mode(type);
}