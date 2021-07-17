#include "vDuneCore/Public/Avatar/Interfaces/Modes/AvatarMode.h"
#include "Blueprint/UserWidget.h"

UAvatarMode::UAvatarMode()
{
}

TSubclassOf<class UUserWidget>  UAvatarMode::get_hud_type() const
{
    return hud_widget_;
}

EAvatarMode UAvatarMode::get_mode_type() const
{
    return mode_type_;
}

void UAvatarMode::setup(APawn * pawn, FTimerManager *manager)
{
    manager_ = manager;
    pawn_ = pawn;

    if (manager_)
        manager_->SetTimer(timer_handle_, this, &UAvatarMode::update, 0.25f, true, 0.0f);
}

void UAvatarMode::teardown()
{
    if (manager_)
        manager_->ClearTimer(timer_handle_);
}

void UAvatarMode::update()
{

}

FTransform UAvatarMode::calculate_camera_displacement(FVector avatar_forward_vector, FVector avatar_world_location)
{
    return FTransform(FRotator(), avatar_world_location, FVector(1));
}

float UAvatarMode::calculate_camera_arm_length()
{
    return 300.0f;
}