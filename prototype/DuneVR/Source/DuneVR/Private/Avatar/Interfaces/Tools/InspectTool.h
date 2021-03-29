#pragma once

#include "CoreMinimal.h"
#include "vDuneCore/Public/Avatar/Interfaces/Tools/AvatarTool.h"
#include "InspectTool.generated.h"

/**
 * 
 */
UCLASS()
class UInspectTool : public UAvatarTool
{
	GENERATED_BODY()

public:
    UInspectTool();
	virtual ~UInspectTool();

    virtual void update() override;

    UFUNCTION(BlueprintCallable, Category=Tools)
    class ASubject * get_inspect_subject() const;

protected:
    virtual void setup(class APawn * pawn, FTimerManager *manager) override;
    virtual FVector calculate_camera_displacement(FVector avatar_forward_vector, FVector avatar_world_location) override;
    virtual float calculate_camera_arm_length() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=InspectTool)
    FName socket_name_;

    class ASubject * subject_;
};
