// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservableActor.h"
#include "../../DuneAvatar.h"
#include "../ViableInteraction.h"
#include "ObjectViewer.h"

// Sets default values
AObservableActor::AObservableActor()
: APalpableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("observable_mesh"));
    RootComponent = mesh_;
}

// Called when the game starts or when spawned
void AObservableActor::BeginPlay()
{
	Super::BeginPlay();

	viewer_ = GetWorld()->SpawnActor<AObjectViewer>(this->GetActorLocation(), FRotator());

    viewer_->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void AObservableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AObservableActor::actor_interaction_viable(const ADuneAvatar * const avatar) const
{
    if (!avatar)
        return false;

    FVector point1 = this->GetActorLocation();
    FVector point2 = avatar->GetActorLocation();

    FVector displacement3D = point2 - point1;
    FVector2D displacement = FVector2D(displacement3D.X, displacement3D.Y);

    return (displacement.Size() < interaction_radius_);
}

void AObservableActor::interact(ADuneAvatar * const avatar, UViableInteraction * interaction, bool &is_active)
{
    if (!avatar)
        return;

    APalpableActor::interact(avatar, interaction, is_active);

    if (!is_active)
    {
        if (avatar->Controller)
        {
            UE_LOG(LogClass, Log, TEXT("%s is possessing %s"), *avatar->GetName(), *this->GetName());
            avatar->Controller->Possess( viewer_ );
            is_active = true;
        }
    }
    else
    {
        if (avatar->Controller)
        {
            UE_LOG(LogClass, Log, TEXT("%s is unpossessing %s"), *avatar->GetName(), *this->GetName());
            avatar->Controller->Possess( avatar );
            is_active = false;
        }
    }
}