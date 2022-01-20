#include "vDuneCore/Public/Avatar/Interfaces/Tools/BallDropExperimentTool.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"

#include "vDuneCore/Private/Avatar/Interfaces/Tools/BallDropExperiment/Models/BallState.h"
#include "Ball/Ball.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/InputSettings.h"
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

    /// Bind Actions to Key Mappings
    FInputActionBinding BallDropExperimentReleaseBinding( "BallDropRelease", IE_Released );
    BallDropExperimentReleaseBinding.ActionDelegate.GetDelegateForManualSet().BindLambda( [this]()
    {
        this->release_ball();
    });

    /// Spawn the Ball
    auto local_transform = FVector(75, 0, 65);
    ball_ = GetWorld()->SpawnActor<ABall>(ball_type_, local_transform, FRotator(0), FActorSpawnParameters());

    /// Keep relative transform will set the origin of the object's transform to the
    /// origin of the avatar.
    ball_->AttachToActor(pawn, FAttachmentTransformRules::KeepRelativeTransform);

    UUserWidget * widget = nullptr;
    auto controller = pawn_->GetController<ADuneController>();
    if (controller)
    {
        /// Create the widget from a widget class.
        widget = controller->new_widget( ball_->widget() );

        /// Add action bindings to the controller.
        auto handle = controller->add_binding(BallDropExperimentReleaseBinding);
        input_binding_handles_.Add( handle );
    }
    /// Called when the controller is null or not a Dune Controller.
    else
    {
        UE_LOG(LogClass, Error, TEXT("No Controller"));
    }


    if (widget) ball_->set_widget( widget );
    else UE_LOG(LogClass, Error, TEXT("No widget"));
}

void UBallDropExperimentTool::teardown()
{
    UAvatarTool::teardown();

    if (!ball_->IsPendingKill())
        ball_->Destroy();

    for(int32 handle : input_binding_handles_)
    {
        auto controller = pawn_->GetController<ADuneController>();
        if (!controller) break;

        controller->remove_binding( handle );
    }
}

void UBallDropExperimentTool::update()
{
    UAvatarMode::update();

    FVector vector = FVector(0);

    auto avatar = Cast<ADuneAvatar>(pawn_);
    if (avatar)
    {
        auto camera = avatar->get_follow_camera();
        if (camera) vector = camera->GetComponentLocation();
    }

    ball_->face_camera( vector );
}

FTransform UBallDropExperimentTool::calculate_camera_displacement(FVector forward, FVector start)
{
    auto up_vector = FVector(0,0,1);

    auto vec = (FVector::CrossProduct(up_vector, forward) * 100) + start + FVector(0,0,25);
    return FTransform(FRotator(), vec, FVector(1));
}

float UBallDropExperimentTool::calculate_camera_arm_length()
{
    return 300.0f;
}

void UBallDropExperimentTool::release_ball()
{
    UE_LOG(LogClass, Log, TEXT("Release ball."));
    ball_->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    ball_->drop();
}

TArray<UBallState*> UBallDropExperimentTool::ball_state() const
{
    TArray<class UBallState*> empty;

    return (ball_) ? ball_->states() : empty;
}
