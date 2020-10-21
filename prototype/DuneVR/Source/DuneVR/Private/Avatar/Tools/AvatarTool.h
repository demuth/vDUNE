// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Modes/AvatarMode.h"
#include "EAvatarTool.h"
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

	EAvatarTool get_tool_type();

protected:
    EAvatarTool tool_type_;
};
