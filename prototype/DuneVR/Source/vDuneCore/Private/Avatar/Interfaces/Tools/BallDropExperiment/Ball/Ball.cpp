#include "Avatar/Interfaces/Tools/BallDropExperiment/Ball/Ball.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABall::ABall()
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
}

TSubclassOf<UUserWidget> ABall::widget() const
{
    return ball_widget_;
}

void ABall::set_widget(UUserWidget* widget)
{
    widget_->SetWidget( widget );
}

void ABall::face_camera(FVector camera_location)
{
    FVector widget_location = widget_->GetComponentLocation();
    FVector vector = camera_location - widget_location;

    widget_->SetWorldRotation( vector.Rotation() );
}

