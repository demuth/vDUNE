#include "User/MenuUser.h"
#include "vDuneCore/Public/Avatar/Interfaces/Modes/AvatarMode.h"

// Sets default values
AMenuUser::AMenuUser(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    available_mode_.Add(EMenu::Initial, nullptr);
}

// Called when the game starts or when spawned
void AMenuUser::BeginPlay()
{
	Super::BeginPlay();

    TSubclassOf<UAvatarMode>* type = available_mode_.Find(EMenu::Initial);
	this->set_user_mode(type);
}

// Called every frame
void AMenuUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMenuUser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

