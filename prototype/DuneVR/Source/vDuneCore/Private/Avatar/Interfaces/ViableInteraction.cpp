// Fill out your copyright notice in the Description page of Project Settings.


#include "vDuneCore/Public/Avatar/Interfaces/ViableInteraction.h"
#include "vDuneCore/Public/Avatar/Interfaces/PalpableActor.h"
#include "GameFramework/Pawn.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"

UViableInteraction::UViableInteraction()
: is_active_(false)
{

}

void UViableInteraction::initialize(class ADuneAvatar * avatar, class APalpableActor * object)
{
    avatar_ = avatar;
    palpable_object_ = object;
}

FString UViableInteraction::generate_user_instruction()
{
    return FString::Printf(TEXT("Press the I key to pickup %s"), *palpable_object_->GetName());
}

bool UViableInteraction::is_viable()
{
    if (!avatar_ || avatar_->IsPendingKill())
    {
        UE_LOG(LogClass, Error, TEXT("Interaction was not initialized. "))
        return false;
    }

    if (!palpable_object_ || palpable_object_->IsPendingKill())
    {
        UE_LOG(LogClass, Error, TEXT("Interaction was not initialized. "))
        return false;
    }

    return palpable_object_->actor_interaction_viable( avatar_ );
}

void UViableInteraction::commit()
{
    /// Check that the Avatar pointer is valid and not being destroyed.
    if (!avatar_ || avatar_->IsPendingKill())
    {
        UE_LOG(LogClass, Error, TEXT("Interaction was not initialized. "))
        return;
    }

    /// Check that the object pointer is valid and not being destroyed.
    if (!palpable_object_ || palpable_object_->IsPendingKill())
    {
        UE_LOG(LogClass, Error, TEXT("Interaction was not initialized. "))
        return;
    }

    /// Initiate the interaction.
    palpable_object_->interact( avatar_, this, is_active_ );
}