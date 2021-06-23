#include "vDuneCore/Public/Avatar/Interfaces/Tools/BallDropExperimentTool.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Camera/CameraComponent.h"

UBallDropExperimentTool::UBallDropExperimentTool()
: UAvatarTool()
{
    tool_type_ = EAvatarTool::BallDropExperiment;
}

void UBallDropExperimentTool::setup(APawn * pawn, FTimerManager *manager)
{
    UAvatarMode::setup(pawn, manager);
}

void UBallDropExperimentTool::teardown()
{
    UAvatarTool::teardown();
}


void UBallDropExperimentTool::update()
{
    UAvatarMode::update();
}

FVector UBallDropExperimentTool::calculate_camera_displacement(FVector forward, FVector start)
{
    auto up_vector = FVector(0,0,1);

    return (FVector::CrossProduct(up_vector, forward) * 100) + start + FVector(0,0,25);
}

float UBallDropExperimentTool::calculate_camera_arm_length()
{
    return 150.0f;
}