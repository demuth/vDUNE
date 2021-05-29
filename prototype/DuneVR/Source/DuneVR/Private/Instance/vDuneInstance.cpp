#include "Instance/vDuneInstance.h"
#include "Blueprint/UserWidget.h"

UvDuneInstance::UvDuneInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UvDuneInstance::OnCreateSessionComplete);
    OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UvDuneInstance::OnStartOnlineGameComplete);
    OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UvDuneInstance::OnFindSessionsComplete);
    OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UvDuneInstance::OnJoinSessionComplete);
    OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UvDuneInstance::OnDestroySessionComplete);
}

UvDuneInstance::~UvDuneInstance() = default;

void UvDuneInstance::Init()
{
    UE_LOG(LogClass, Log, TEXT("*** Instance Init ***"));
    set_state(ApplicationState::Initial);
}


void UvDuneInstance::Shutdown()
{
    UE_LOG(LogClass, Log, TEXT("*** Instance Shutdown ***"));
}

void UvDuneInstance::set_state(ApplicationState new_state)
{
    if (state_ != new_state) handle_state(new_state);
}

// handles changes in the application state.
void UvDuneInstance::handle_state(ApplicationState new_state)
{
    switch(new_state)
    {
        case ApplicationState::Initial: on_initial_state(); break;
        case ApplicationState::Active: on_active_state(); break;
    }
}

void UvDuneInstance::on_initial_state()
{
    UE_LOG(LogClass, Log, TEXT("~~~ Initial State ~~~"));

//    for(FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
//    {
//        UE_LOG(LogClass, Log, TEXT("Pawn found."));
//    }
}

void UvDuneInstance::StartOnlineGame()
{
    ULocalPlayer* const Player = GetFirstGamePlayer();

    HostSession(Player->GetPreferredUniqueNetId(), GameSessionName, true, true, 4);
}

void UvDuneInstance::FindOnlineGames()
{
    ULocalPlayer* const Player = GetFirstGamePlayer();

    FindSessions(Player->GetPreferredUniqueNetId(), true, true);
}

void UvDuneInstance::JoinOnlineGame()
{
    ULocalPlayer* const Player = GetFirstGamePlayer();

    // Just a SearchResult where we can save the one we want to use, for the case we find more than one!
    FOnlineSessionSearchResult SearchResult;

    // If the Array is not empty, we can go through it
    if (SessionSearch->SearchResults.Num() > 0)
    {
        for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
        {
            // To avoid something crazy, we filter sessions from ourself
            if (SessionSearch->SearchResults[i].Session.OwningUserId != Player->GetPreferredUniqueNetId())
            {
                SearchResult = SessionSearch->SearchResults[i];

                // Once we found sounce a Session that is not ours, just join it. Instead of using a for loop, you could
                // use a widget where you click on and have a reference for the GameSession it represents which you can use
                // here
                join_session(Player->GetPreferredUniqueNetId(), GameSessionName, SearchResult);
                break;
            }
        }
    }
}

void UvDuneInstance::DestroySessionAndLeaveGame()
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

        if (Sessions.IsValid())
        {
            Sessions->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);

            Sessions->DestroySession(GameSessionName);
        }
    }
}

bool UvDuneInstance::HostSession(FUniqueNetIdRepl UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
    IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

        if (Sessions.IsValid() && UserId.IsValid())
        {
            SessionSettings = MakeShareable(new FOnlineSessionSettings());

            SessionSettings->bIsLANMatch = bIsLAN;
            SessionSettings->bUsesPresence = bIsPresence;
            SessionSettings->NumPublicConnections = MaxNumPlayers;
            SessionSettings->NumPrivateConnections = 0;
            SessionSettings->bAllowInvites = true;
            SessionSettings->bAllowJoinInProgress = true;
            SessionSettings->bShouldAdvertise = true;
            SessionSettings->bAllowJoinViaPresence = true;
            SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

            SessionSettings->Set(SETTING_MAPNAME, FString("NewMap"), EOnlineDataAdvertisementType::ViaOnlineService);

            OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

            return Sessions->CreateSession(*UserId, SessionName, *SessionSettings);
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No online system found."));
    }

    return false;
}

void UvDuneInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

        if (Sessions.IsValid())
        {
            Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
            if (bWasSuccessful)
            {
                OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
                Sessions->StartSession(SessionName);
            }
        }
    }
}

void UvDuneInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

    // Get the Online Subsystem so we can get the Session Interface
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        // Get the Session Interface to clear the Delegate
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
        if (Sessions.IsValid())
        {
            // Clear the delegate, since we are done with this call
            Sessions->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
        }
    }

    // If the start was successful, we can open a NewMap if we want. Make sure to use "listen" as a parameter!
    if (bWasSuccessful)
    {
        UGameplayStatics::OpenLevel(GetWorld(), "NeutrinoSandBox", true, "listen");
    }
}

void UvDuneInstance::FindSessions(FUniqueNetIdRepl UserId, bool bIsLAN, bool bIsPresence)
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

        if (Sessions.IsValid() && UserId.IsValid())
        {
            SessionSearch = MakeShareable(new FOnlineSessionSearch());

            SessionSearch->bIsLanQuery = bIsLAN;
            SessionSearch->MaxSearchResults = 20;
            SessionSearch->PingBucketSize = 50;

            if (bIsPresence)
            {
                SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
            }

            TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();

            OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

            Sessions->FindSessions(*UserId, SearchSettingsRef);
        }
    }
    else
    {
        OnFindSessionsComplete(false);
    }
}

void UvDuneInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OFindSessionsComplete bSuccess: %d"), bWasSuccessful));

    IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
        if (Sessions.IsValid())
        {
            Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));

            if (SessionSearch->SearchResults.Num() > 0)
            {
                for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session Number: %d | Sessionname: %s "), SearchIdx+1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName)));
                }
            }
        }
    }
}

bool UvDuneInstance::join_session(FUniqueNetIdRepl UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
    bool bSuccessful = false;

    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

        if (Sessions.IsValid() && UserId.IsValid())
        {
            OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

            bSuccessful = Sessions->JoinSession(*UserId, SessionName, SearchResult);
        }
    }

    return bSuccessful;
}

void UvDuneInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int32>(Result)));

    // Get the OnlineSubsystem we want to work with
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

        if (Sessions.IsValid())
        {
            Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

            APlayerController * const PlayerController = GetFirstLocalPlayerController();

            FString TravelURL;

            if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
            {
                PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
            }
        }
    }
}

void UvDuneInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnDestroySessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

        if (Sessions.IsValid())
        {
            Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);

            if (bWasSuccessful)
            {
                UGameplayStatics::OpenLevel(GetWorld(), "Landing", true);
            }
        }
    }
}

void UvDuneInstance::on_active_state()
{

}