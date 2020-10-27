// Fill out your copyright notice in the Description page of Project Settings.


#include "../InspectTool.h"
#include "../../DuneAvatar.h"
#include "GameFramework/Pawn.h"
#include "Engine/StaticMeshActor.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "../../Interfaces/Inspectable/Subject.h"


UInspectTool::UInspectTool()
: UAvatarTool()
{
    tool_type_ = EAvatarTool::InspectTool;
}

UInspectTool::~UInspectTool()
{
}

void UInspectTool::setup(APawn * pawn, FTimerManager *manager)
{
    UAvatarMode::setup(pawn, manager);
}


void UInspectTool::update()
{
    UAvatarMode::update();

    ADuneAvatar * avatar = Cast<ADuneAvatar>(pawn_);

    if (!avatar)
        return;

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
            DrawDebugLine(GetWorld(), (avatar_mesh != nullptr)?avatar_mesh->GetSocketLocation(socket_name_):start + FVector(0,300,0), result.ImpactPoint, FColor::Cyan, false, 0.5f, 0, 1);
            DrawDebugSphere(GetWorld(), result.ImpactPoint, 20, 12, FColor(181,0,0), false, 1.0f, 0, 2);

            auto subject = Cast<ASubject>(result.Actor);

            if (subject)
                UE_LOG(LogClass, Log, TEXT("You pointed at %s"), *subject->get_name());
        }
    }
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