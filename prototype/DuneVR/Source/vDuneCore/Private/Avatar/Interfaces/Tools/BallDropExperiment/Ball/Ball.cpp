#include "Avatar/Interfaces/Tools/BallDropExperiment/Ball/Ball.h"
#include "Components/WidgetComponent.h"

#include <PhysicsLib/PhysicsLib.h>

// Sets default values
ABall::ABall()
: state_(BallDropState::Held)
, velocity_(0)
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
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (state_ == BallDropState::Released)
	{
	    UE_LOG(LogClass, Log, TEXT("Ball is in free fall..."));

	    Velocity v;
	    v.magnitude = 0;
	    v.direction.x = 0;
	    v.direction.y = 0;
	    v.direction.z = velocity_;

	    /// Calculate fall distance and final velocity using meters and meters/second
	    double distance_in_meters = free_fall_distance( DeltaTime,  v );
	    velocity_ = velocity_at_time_interval( DeltaTime, v );

	    /// Unit conversions
	    double distance_in_centimeters = distance_in_meters * 100;

	    /// Update position based on calculated distance.
	    FVector position = this->GetActorLocation();
	    position = position + FVector(0, 0, distance_in_centimeters);
	    this->SetActorLocation(position);

	    UE_LOG(LogClass, Log, TEXT("Ball fell %f distance since last frame was drawn.  Final velocity %f"), distance_in_meters, velocity_);
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
    state_ = BallDropState::Released;
}

