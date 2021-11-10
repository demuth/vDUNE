#include "vDuneCore/Public/Avatar/DuneController.h"
#include "vDuneCore/Public/Avatar/DuneAvatar.h"
#include "vDuneCore/Public/Avatar/DuneHUD.h"
#include "vDuneCore/Public/Avatar/Interfaces/Observable/ObjectViewer.h"
#include "Blueprint/UserWidget.h"

ADuneController::ADuneController()
{

}

void ADuneController::BeginPlay()
{
    Super::BeginPlay();
}

void ADuneController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Set up menu key bindings
    InputComponent->BindAction("ShowCollectibles", IE_Released, this, &ADuneController::toggle_collectibles_display);

    InputComponent->BindAction("ServerMenu", IE_Released, this, &ADuneController::toggle_server_menu);

    // Interaction bindings
    InputComponent->BindAction("Interact", IE_Released, this, &ADuneController::on_interaction_command);
}

void ADuneController::toggle_collectibles_display()
{
    UE_LOG(LogClass, Log, TEXT("toggle collectible screen"));
    ADuneAvatar * avatar = Cast<ADuneAvatar>(GetPawn());

    if (avatar)
    {
        avatar->set_mode(EAvatarMode::Menu);
    }
}

void ADuneController::toggle_server_menu()
{
    UE_LOG(LogClass, Log, TEXT("toggle server menu"));
    ADuneAvatar * avatar = Cast<ADuneAvatar>(GetPawn());

    if (avatar)
    {
        avatar->set_mode(EAvatarMode::ServerMenu);
    }
}

void ADuneController::on_interaction_command()
{
    auto avatar = Cast<ADuneAvatar>(GetPawn());
    auto viewer = Cast<AObjectViewer>(GetPawn());

    if (avatar)
        avatar->try_interaction();

    else if (viewer)
        viewer->try_end_viewer_session();
}

void ADuneController::close_menu()
{
    UE_LOG(LogClass, Log, TEXT("Attempting to close the menu. . ."));
    ADuneAvatar * avatar = Cast<ADuneAvatar>(GetPawn());

    if (avatar != nullptr)
    {
        avatar->set_mode(EAvatarMode::Roam);
    }
    else
    {
        UE_LOG(LogClass, Error, TEXT("Failed to close the menu. "));
    }
}

UUserWidget * ADuneController::update_hud()
{
    auto hud = GetHUD<ADuneHUD>();

    if (hud != nullptr)
    {
        return hud->update_hud_widget();
    }
    else
    {
        UE_LOG(LogClass, Warning, TEXT("Controller could not update the hud. "));
        return nullptr;
    }
}

UUserWidget * ADuneController::new_widget(TSubclassOf<UUserWidget> type)
{
    return CreateWidget<UUserWidget>(this, type);
}

int32 ADuneController::add_binding(FInputActionBinding binding)
{
    auto bound = InputComponent->AddActionBinding( binding );
    return bound.GetHandle();
}

void ADuneController::remove_binding(int32 handle)
{
    InputComponent->RemoveActionBindingForHandle( handle );
}