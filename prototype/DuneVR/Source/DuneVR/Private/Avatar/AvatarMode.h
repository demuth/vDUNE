// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AvatarMode.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class UAvatarMode : public UObject
{
    GENERATED_BODY()

public:
    UAvatarMode();
    TSubclassOf<class UUserWidget> get_hud_type() const;

    virtual void setup(class APawn * pawn, FTimerManager *manager);
    virtual void teardown();

    virtual FVector calculate_camera_displacement(FVector avatar_forward_vector, FVector avatar_world_location);
    virtual float calculate_camera_arm_length();

protected:
    virtual void update();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widgets)
    TSubclassOf<class UUserWidget> hud_widget_;

    class APawn * pawn_;

private:
    FTimerManager *manager_;
    FTimerHandle timer_handle_;
};
