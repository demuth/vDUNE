// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"


void UCollectible::Initialize(FString name, FString details)
{
    collectible_name = name;
    collectible_details = details;
}