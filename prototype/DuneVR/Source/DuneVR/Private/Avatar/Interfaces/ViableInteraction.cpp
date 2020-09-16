// Fill out your copyright notice in the Description page of Project Settings.


#include "ViableInteraction.h"
#include "PalpableActor.h"
#include "GameFramework/Pawn.h"
#include "../DuneAvatar.h"

void UViableInteraction::initialize(class APawn * pawn, class APalpableActor * object)
{
    pawn_ = pawn;
    palpable_object_ = object;
}

bool UViableInteraction::is_viable()
{
    if (!pawn_ || !palpable_object_)
    {
        UE_LOG(LogClass, Error, TEXT("Interaction was not initialized. "))
        return false;
    }

    return palpable_object_->actor_interaction_viable(pawn_);
}

void UViableInteraction::commit()
{
    if (!pawn_ || !palpable_object_)
    {
        UE_LOG(LogClass, Error, TEXT("Interaction was not initialized. "))
        return;
    }

    palpable_object_->interact(Cast<ADuneAvatar>(pawn_));
}