#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine.h"
#include "Online.h"
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
    UvDuneInstance(const FObjectInitializer& ObjectInitializer);
    ~UvDuneInstance();


    virtual void Init() override;
    virtual void Shutdown() override;

    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void StartOnlineGame();

    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void FindOnlineGames();

    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void JoinOnlineGame();

    UFUNCTION(BlueprintCallable, Category = "Network|Test")
    void DestroySessionAndLeaveGame();

    /// *** ONLINE FUNCTIONS ***
    /// HOSTING
    bool HostSession(FUniqueNetIdRepl UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
    virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

    /// FINDING
    void FindSessions(FUniqueNetIdRepl UserId, bool bIsLAN, bool bIsPresence);
    void OnFindSessionsComplete(bool bWasSuccessful);

    /// JOINING
    virtual bool join_session(FUniqueNetIdRepl UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

    /// DESTROY A SESSION
    virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
    /// *** END ONLINE FUNCTIONS ***

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widgets)
    TSubclassOf<class UUserWidget> initial_menu_widget_;

private:
    void set_state(ApplicationState new_state);

    ApplicationState state_;

    void handle_state(ApplicationState state);

    void on_initial_state();
    void on_active_state();

    /// Create and Start Session Delegates
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

    /// Create and Start Session Handles
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;
    FDelegateHandle OnStartSessionCompleteDelegateHandle;

    /// Find sessions Delegates and Handles
    FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
    FDelegateHandle OnFindSessionsCompleteDelegateHandle;

    /// Join session
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
    FDelegateHandle OnJoinSessionCompleteDelegateHandle;

    /// Destroy a session
    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
    FDelegateHandle OnDestroySessionCompleteDelegateHandle;

    TSharedPtr<class FOnlineSessionSettings> SessionSettings;
    TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
