#pragma once

#include "CoreMinimal.h"
#include "Avatar/Interfaces/Tools/AvatarTool.h"
#include "BallDropExperimentTool.generated.h"

UCLASS()
class UBallDropExperimentTool : public UAvatarTool
{
	GENERATED_BODY()

public:
    UBallDropExperimentTool();
	virtual ~UBallDropExperimentTool() = default;

    virtual void update() override;

protected:
    virtual void setup(class APawn * pawn, FTimerManager *manager) override;
    virtual void teardown() override;
    virtual FTransform calculate_camera_displacement(FVector avatar_forward_vector, FVector avatar_world_location) override;
    virtual float calculate_camera_arm_length() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widgets)
    TSubclassOf<class ABall> ball_type_;

private:
    ABall *ball_;
    APawn *pawn_;
};
