// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../AvatarMode.h"
#include "AvatarTool.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, ConversionRoot)
class UAvatarTool : public UAvatarMode
{
	GENERATED_BODY()

public:
    UAvatarTool();

	virtual void update() override;

protected:
    virtual void setup(class APawn * pawn, FTimerManager *manager) override;
    virtual FVector calculate_camera_displacement(FVector avatar_forward_vector, FVector avatar_world_location) override;
    virtual float calculate_camera_arm_length() override;

private:

};
