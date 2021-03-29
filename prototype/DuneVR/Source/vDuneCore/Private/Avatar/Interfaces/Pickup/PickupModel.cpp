// Fill out your copyright notice in the Description page of Project Settings.


#include "vDuneCore/Public/Avatar/Interfaces/Pickup/PickupModel.h"

void UPickupModel::Initialize(FString name, FString details)
{
    collectible_name_ = name;
    collectible_details_ = details;
}

FString UPickupModel::get_name() const
{
    return collectible_name_;
}

FString UPickupModel::get_details() const
{
    return collectible_details_;
}