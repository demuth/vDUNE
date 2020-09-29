// Fill out your copyright notice in the Description page of Project Settings.


#include "PalpableActor.h"
#include "../DuneAvatar.h"
#include "ViableInteraction.h"

// Sets default values
APalpableActor::APalpableActor()
: interaction_radius_(100.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APalpableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APalpableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APalpableActor::actor_interaction_viable(const ADuneAvatar * const actor) const
{
    return true;
}


void APalpableActor::interact(ADuneAvatar * const avatar, UViableInteraction * interaction, bool &is_active)
{
    if (this->actor_interaction_viable(avatar))
        viable_interactions_.Add(avatar->GetName(), interaction);
}