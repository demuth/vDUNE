#include "DefaultGameMode.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "vDuneCore/Public/User/MenuUser.h"

#include "Kismet/GameplayStatics.h"

ADefaultGameMode::ADefaultGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void ADefaultGameMode::BeginPlay()
{
    Super::BeginPlay();
}

UDuneState ADefaultGameMode::get_state()
{
    return UDuneState::Select;
}