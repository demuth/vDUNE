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

