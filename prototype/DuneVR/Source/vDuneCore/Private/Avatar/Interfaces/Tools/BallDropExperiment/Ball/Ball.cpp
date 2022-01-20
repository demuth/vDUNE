#include "Avatar/Interfaces/Tools/BallDropExperiment/Ball/Ball.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"

#include "vDuneCore/Private/Avatar/Interfaces/Tools/BallDropExperiment/Models/BallState.h"

#include <PhysicsLib/PhysicsLib.h>

// Sets default values
ABall::ABall()
: state_(BallState::HeldAboveGround)
, velocity_(20.0f)
, total_time_in_free_fall_(0.0f)
, total_distance_in_free_fall_(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ball_mesh"));
	RootComponent = mesh_;

	widget_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	widget_->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	mesh_->SetCollisionProfileName(TEXT("WorldStatic"));

	SetActorEnableCollision(ECollisionEnabled::QueryOnly);

    mesh_->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
    mesh_->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
    mesh_->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (state_ == BallState::FreeFall)
	{
	    UE_LOG(LogClass, Log, TEXT("Ball is in free fall..."));
	    total_time_in_free_fall_ += DeltaTime;

	    Velocity v;
	    v.magnitude = 0;
	    v.direction.x = 100.0f;
	    v.direction.y = 0;
	    v.direction.z = velocity_;

	    /// Calculate fall distance and final velocity using meters and meters/second
	    double distance_in_meters = free_fall_distance( DeltaTime,  v );
	    velocity_ = velocity_at_time_interval( DeltaTime, v );

	    total_distance_in_free_fall_ += distance_in_meters;

	    /// Unit conversions
	    double distance_in_centimeters = distance_in_meters * 100;

	    /// Update position based on calculated distance.
	    FVector old_position = this->GetActorLocation();
	    FVector new_position = old_position + FVector(v.direction.x * DeltaTime, v.direction.y * DeltaTime, distance_in_centimeters);
	    this->SetActorLocation(new_position);

	    DrawDebugLine(GetWorld(), old_position, new_position, FColor::Cyan, false, 1.5f, 0, 1);

	    add_state(FVector(0, 0, velocity_), total_distance_in_free_fall_, total_time_in_free_fall_);
	    UE_LOG(LogClass, Log, TEXT("Ball fell %f distance since last frame was drawn (dt %f).  Final velocity %f.  Ball has fallen a total of %f meters for a time of %f seconds."), distance_in_meters, DeltaTime, velocity_, total_distance_in_free_fall_, total_time_in_free_fall_);
	}
}

TSubclassOf<UUserWidget> ABall::widget() const
{
    return ball_widget_;
}

void ABall::set_widget(UUserWidget* widget)
{
    widget_->SetWidget( widget );
    widget_->SetOnlyOwnerSee(false);
    widget_->SetIsReplicated(false);
    widget_->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    widget_->SetDrawSize(FVector2D(1920, 1080));
    widget_->SetRelativeScale3D(FVector(.5f, .5f, .5f));

    /// collision channels
    widget_->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    widget_->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    widget_->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    /// block camera & visibility for mouse cursor
    widget_->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
    widget_->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void ABall::face_camera(FVector camera_location)
{
    FVector widget_location = widget_->GetComponentLocation();
    FVector vector = camera_location - widget_location;

    widget_->SetWorldRotation( vector.Rotation() );
}

void ABall::drop()
{
    state_ = BallState::FreeFall;
}

void ABall::NotifyHit
(class UPrimitiveComponent * MyComp, AActor * Other, class UPrimitiveComponent * OtherComp, bool bSelfMoved,
        FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
    UE_LOG(LogClass, Log, TEXT("Its a hit."));
}

void ABall::NotifyActorBeginOverlap(AActor * OtherActor)
{
    UE_LOG(LogClass, Log, TEXT("Its an overlap. %s"), *FString(OtherActor->GetName()));
    state_ = BallState::Unknown;
}

void ABall::add_state(FVector velocity, double distance, double time)
{
    UBallState* ball_state = NewObject<UBallState>();

    ball_state->set(velocity, distance, time);

    array_.Add( ball_state );
}

TArray<UBallState*> ABall::states() const
{
    return array_;
}