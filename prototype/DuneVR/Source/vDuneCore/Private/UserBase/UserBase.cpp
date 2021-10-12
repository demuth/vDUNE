#include "UserBase/UserBase.h"

// Sets default values
AUserBase::AUserBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUserBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUserBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUserBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAvatarMode* AUserBase::get_user_mode() const
{
    return mode_;
}

void AUserBase::set_user_mode(TSubclassOf<UAvatarMode>* type)
{
    UE_LOG(LogClass, Log, TEXT("Setting User Type: "));
    auto controller = this->GetController<ADuneController>();

    //tear down any existing mode.
    if (mode_ != nullptr)
    {
        mode_->teardown();
    }

    if (!type || type->Get() == nullptr)
    {
        UE_LOG(LogClass, Error, TEXT("Menu class was not found. "));
        mode_ = nullptr;
    }
    else
    {
        //assign a new mode instance and set it up.
        if (controller != nullptr)
        {
            mode_ = NewObject<UAvatarMode>(this, type->Get());
            controller->update_hud();

            //mode_ was reassigned therefore check that it is still valid.
            if (mode_ != nullptr)
                mode_->setup( this, &GetWorldTimerManager() );
            else
                UE_LOG(LogClass, Error, TEXT("Could not set mode: mode could not be setup. "));
        }
        else
            UE_LOG(LogClass, Error, TEXT("Could not set mode: controller was not valid. "));
    }
}