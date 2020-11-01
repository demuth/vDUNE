// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar/Interfaces/Tools/AvatarTool.h"
#include "MeasureTool.generated.h"

/**
 * 
 */
UCLASS()
class UMeasureTool : public UAvatarTool
{
	GENERATED_BODY()

public:
    UMeasureTool();
	virtual ~UMeasureTool() = default;

    virtual void update() override;

    void add_marker();

protected:
    virtual void setup(class APawn * pawn, FTimerManager *manager) override;
    virtual void teardown() override;
    virtual FVector calculate_camera_displacement(FVector avatar_forward_vector, FVector avatar_world_location) override;
    virtual float calculate_camera_arm_length() override;

    UFUNCTION(BlueprintCallable, Category=Data)
    FORCEINLINE TArray<class AMeasurement *> get_measurements() const { return measurement_; }

private:
    TArray<class AMeasureMarker *> marker_;
    TArray<class AMeasurement *> measurement_;

    FVector * location_;

    void clear();
};
