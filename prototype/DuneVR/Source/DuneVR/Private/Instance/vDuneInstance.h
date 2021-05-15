#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "vDuneInstance.generated.h"

enum class ApplicationState
{
    Unknown,
    Initial,
    Active
};

UCLASS()
class UvDuneInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    UvDuneInstance();
    ~UvDuneInstance();


    virtual void Init() override;
    virtual void Shutdown() override;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widgets)
    TSubclassOf<class UUserWidget> initial_menu_widget_;

private:
    void set_state(ApplicationState new_state);

    ApplicationState state_;

    void handle_state(ApplicationState state);

    void on_initial_state();
    void on_active_state();
};
