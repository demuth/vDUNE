#include "../InspectTool.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "GameFramework/Pawn.h"
#include "Engine/StaticMeshActor.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "vDuneCore/Public/Avatar/Interfaces/Inspectable/Subject.h"


UInspectTool::UInspectTool()
: UAvatarTool()
{
    tool_type_ = EAvatarTool::InspectTool;
}

UInspectTool::~UInspectTool() = default;

void UInspectTool::setup(APawn * pawn, FTimerManager *manager)
{
    UAvatarMode::setup(pawn, manager);
}


void UInspectTool::update()
{
    UAvatarMode::update();

    ADuneAvatar * avatar = Cast<ADuneAvatar>(pawn_);

    if (!avatar) return;
    auto avatar_mesh = avatar->GetMesh();

    auto up = FVector(0, 0, 1);
    auto forward = avatar->get_follow_camera()->GetForwardVector();
    FVector start = avatar->GetActorLocation();
    FVector end = ((forward * 1000.0f)) + start;

    FHitResult result;
    FCollisionQueryParams collision_params;
    if (GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, collision_params))
    {
        if(result.bBlockingHit)
        {
            DrawDebugLine(GetWorld(), (avatar_mesh != nullptr)
            ? avatar_mesh->GetSocketLocation(socket_name_)
            : start + FVector(0,300,0), result.ImpactPoint, FColor::Cyan, false, 0.5f, 0, 1);

            DrawDebugSphere(GetWorld(), result.ImpactPoint, 5, 12, FColor::Cyan, false, 1.0f, 0, 2);

            subject_ = Cast<ASubject>(result.Actor);
        }
        else
        {
            subject_ = nullptr;
        }
    }
}

ASubject * UInspectTool::get_inspect_subject() const
{
    return subject_;
}

FVector UInspectTool::calculate_camera_displacement(FVector forward, FVector start)
{
    auto up_vector = FVector(0,0,1);

    return (FVector::CrossProduct(up_vector, forward) * 100) + start + FVector(0,0,25);
}

float UInspectTool::calculate_camera_arm_length()
{
    return 150.0f;
}