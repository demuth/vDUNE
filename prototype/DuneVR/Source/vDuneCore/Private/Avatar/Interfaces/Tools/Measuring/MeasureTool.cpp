#include "vDuneCore/Public/Avatar/Interfaces/Tools/MeasureTool.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "MeasureMarker.h"
#include "Measurement.h"

UMeasureTool::UMeasureTool()
: UAvatarTool()
, location_(nullptr)
{
    tool_type_ = EAvatarTool::MeasureTool;
}

void UMeasureTool::setup(APawn * pawn, FTimerManager *manager)
{
    UAvatarMode::setup(pawn, manager);
}

void UMeasureTool::teardown()
{
    UAvatarTool::teardown();
    this->clear();
}


void UMeasureTool::update()
{
    UAvatarMode::update();

    ADuneAvatar * avatar = Cast<ADuneAvatar>(pawn_);

    if (!avatar || marker_.Num() >= 2)
        return;

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
            FVector impact = result.ImpactPoint;
            DrawDebugLine(GetWorld(), start + FVector(0,0,100), result.ImpactPoint, FColor::Cyan, false, 0.5f, 0, 1);
            DrawDebugSphere(GetWorld(), impact, 20, 12, FColor(181,0,0), false, 1.0f, 0, 2);

            location_ = new FVector(impact);
        }
        else
        {
            delete location_;
            location_ = nullptr;
        }
    }
}

FVector UMeasureTool::calculate_camera_displacement(FVector forward, FVector start)
{
    auto up_vector = FVector(0,0,1);

    return (FVector::CrossProduct(up_vector, forward) * 100) + start + FVector(0,0,25);
}

float UMeasureTool::calculate_camera_arm_length()
{
    return 150.0f;
}

void UMeasureTool::add_marker()
{
    if (marker_.Num() < 2)
    {
        if (location_ != nullptr)
        {
            UE_LOG(LogClass, Log, TEXT("adding marker (%f, %f, %f) . . ."), location_->X, location_->Y, location_->Z);
            auto new_marker = GetWorld()->SpawnActor<AMeasureMarker>(FVector(location_->X, location_->Y, location_->Z), FRotator());
            marker_.Add(new_marker);
        }
        else
        {
            UE_LOG(LogClass, Warning, TEXT("Can't add marker."));
        }

        if (marker_.Num() == 2)
        {
            auto measurement = GetWorld()->SpawnActor<AMeasurement>();

            measurement->set_points(marker_[0], marker_[1], particle_system_);

            measurement_.Add(measurement);
        }
    }
    else
    {
        UE_LOG(LogClass, Warning, TEXT("Too many markers."));
    }
}

void UMeasureTool::clear()
{
    for(auto marker : marker_)
    {
        if (!marker->IsPendingKill())
            marker->Destroy();
    }

    for(auto measurement : measurement_)
    {
        if (!measurement->IsPendingKill())
            measurement->Destroy();
    }
}