// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupModel.h"

void UPickupModel::Initialize(FString name, FString details)
{
    collectible_name_ = name;
    collectible_details_ = details;
}