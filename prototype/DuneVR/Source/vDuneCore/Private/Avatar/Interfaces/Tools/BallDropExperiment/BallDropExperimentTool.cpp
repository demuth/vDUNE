#include "vDuneCore/Public/Avatar/Interfaces/Tools/BallDropExperimentTool.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Camera/CameraComponent.h"
#include "Ball/Ball.h"

UBallDropExperimentTool::UBallDropExperimentTool()
: UAvatarTool()
{
    tool_type_ = EAvatarTool::BallDropExperiment;
}

void UBallDropExperimentTool::setup(APawn * pawn, FTimerManager *manager)
{
    UAvatarMode::setup(pawn, manager);

    auto local_transform = FVector(75, 0, 65);
    ball_ = GetWorld()->SpawnActor<ABall>(ball_type_, local_transform, FRotator(0), FActorSpawnParameters());

    /// Keep relative transform will set the origin of the object's transform to the
    /// origin of the avatar.
    ball_->AttachToActor(pawn, FAttachmentTransformRules::KeepRelativeTransform);
}

void UBallDropExperimentTool::teardown()
{
    UAvatarTool::teardown();

    if (!ball_->IsPendingKill())
        ball_->Destroy();
}


void UBallDropExperimentTool::update()
{
    UAvatarMode::update();
}

FTransform UBallDropExperimentTool::calculate_camera_displacement(FVector forward, FVector start)
{
    auto up_vector = FVector(0,0,1);

    auto vec = (FVector::CrossProduct(up_vector, forward) * 100) + start + FVector(0,0,25);
    return FTransform(FRotator(), vec, FVector(1));
}

float UBallDropExperimentTool::calculate_camera_arm_length()
{
    return 150.0f;
}