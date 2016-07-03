#include "WNox.h"
#include "WNoxGameInstance.h"
#include "ItemInfo.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSessionSettings.h"

UWNoxGameInstance::UWNoxGameInstance(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{

}

void UWNoxGameInstance::Init()
{
	Super::Init();

	ItemInfoManager = NewObject<UItemInfoManager>(this, TEXT("ItemInfoManager"));
	ItemInfoManager->SetCurrentWorld(GetWorld());
	ItemInfoManager->SetFromDataTableObject(ItemInfoDataTable);
}

bool UWNoxGameInstance::HostSession(FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());

	if (OnlineSub)
	{
		// Get the Session Interface, so we can call the "CreateSession" function on it
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			/*
			Fill in all the Session Settings that we want to use.

			There are more with SessionSettings.Set(...);
			For example the Map or the GameMode/Type.
			*/
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsLANMatch = bIsLAN;
			SessionSettings.bUsesPresence = bIsPresence;
			SessionSettings.NumPublicConnections = MaxNumPlayers;
			SessionSettings.NumPrivateConnections = 0;
			SessionSettings.bAllowInvites = true;
			SessionSettings.bAllowJoinInProgress = true;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bAllowJoinViaPresence = true;
			SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
			SessionSettings.Set(SETTING_MAPNAME, FString("GameMap"), EOnlineDataAdvertisementType::ViaOnlineService);
			// Set the delegate to the Handle of the SessionInterface
			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UWNoxGameInstance::OnCreateSessionComplete));
			// Our delegate should get called when this is complete (doesn't need to be successful!)
			return Sessions->CreateSession(0, SessionName, SessionSettings);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsytem found!"));
	}

	return false;
}

void UWNoxGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnCreateSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));
	// Get the OnlineSubsystem so we can get the Session Interface
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());
	if (OnlineSub)
	{
		// Get the Session Interface to call the StartSession function
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			// Clear the SessionComplete delegate handle, since we finished this call
			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				// Set the StartSession delegate handle
				OnStartSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(FOnStartSessionCompleteDelegate::CreateUObject(this, &UWNoxGameInstance::OnStartOnlineGameComplete));
				// Our StartSessionComplete delegate should get called after this
				Sessions->StartSession(SessionName);
			}
		}
	}
}

void UWNoxGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnStartSessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));
	// Get the Online Subsystem so we can get the Session Interface
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());
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
		//UGameplayStatics::OpenLevel(GetWorld(), "GameMap", true, "listen");
	}
}

void UWNoxGameInstance::FindSessions(bool bIsLAN, bool bIsPresence)
{
	// Get the OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());
	if (OnlineSub)
	{
		// Get the SessionInterface from our OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			/*
			Fill in all the SearchSettings, like if we are searching for a LAN game and how many results we want to have!
			*/
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionSearch->bIsLanQuery = bIsLAN;
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->PingBucketSize = 50;

			// We only want to set this Query Setting if "bIsPresence" is true
			if (bIsPresence)
			{
				SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
			}
			TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();
			// Set the Delegate to the Delegate Handle of the FindSession function
			OnFindSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(this, &UWNoxGameInstance::OnFindSessionsComplete));

			// Finally call the SessionInterface function. The Delegate gets called once this is finished
			Sessions->FindSessions(0, SearchSettingsRef);
		}
	}
	else
	{
		// If something goes wrong, just call the Delegate Function directly with "false".
		OnFindSessionsComplete(false);
	}
}

void UWNoxGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OFindSessionsComplete bSuccess: %d"), bWasSuccessful));
	// Get OnlineSubsystem we want to work with
	IOnlineSubsystem* const OnlineSub = Online::GetSubsystem(GetWorld());
	if (OnlineSub)
	{
		// Get SessionInterface of the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			// Clear the Delegate handle, since we finished this call
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
			// Just debugging the Number of Search results. Can be displayed in UMG or something later on
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Num Search Results: %d"), SessionSearch->SearchResults.Num()));

			// If we have found at least 1 session, we just going to debug them. You could add them to a list of UMG Widgets, like it is done in the BP version!
			if (SessionSearch->SearchResults.Num() > 0)
			{
				// "SessionSearch->SearchResults" is an Array that contains all the information. You can access the Session in this and get a lot of information.
				// This can be customized later on with your own classes to add more information that can be set and displayed
				for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
				{
					// OwningUserName is just the SessionName for now. I guess you can create your own Host Settings class and GameSession Class and add a proper GameServer Name here.
					// This is something you can't do in Blueprint for example!
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session Number: %d | Sessionname: %s "), SearchIdx + 1, *(SessionSearch->SearchResults[SearchIdx].Session.OwningUserName)));
				}
			}
		}
	}
}

bool UWNoxGameInstance::JoinSessionCustom(FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	// Return bool
	bool bSuccessful = false;

	// Get OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());

	if (OnlineSub)
	{
		// Get SessionInterface from the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			// Set the Handle again
			OnJoinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(this, &UWNoxGameInstance::OnJoinSessionComplete));

			// Call the "JoinSession" Function with the passed "SearchResult". The "SessionSearch->SearchResults" can be used to get such a
			// "FOnlineSessionSearchResult" and pass it. Pretty straight forward!
			bSuccessful = Sessions->JoinSession(0, SessionName, SearchResult);
		}
	}

	return bSuccessful;
}

void UWNoxGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnJoinSessionComplete %s, %d"), *SessionName.ToString(), static_cast<int32>(Result)));

	// Get the OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());
	if (OnlineSub)
	{
		// Get SessionInterface from the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			// Clear the Delegate again
			Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

			// Get the first local PlayerController, so we can call "ClientTravel" to get to the Server Map
			// This is something the Blueprint Node "Join Session" does automatically!
			APlayerController* PlayerController = GetFirstLocalPlayerController();

			// We need a FString to use ClientTravel and we can let the SessionInterface contruct such a
			// String for us by giving him the SessionName and an empty String. We want to do this, because
			// Every OnlineSubsystem uses different TravelURLs
			FString TravelURL;

			if (PlayerController && Sessions->GetResolvedConnectString(SessionName, TravelURL))
			{
				// Finally call the ClienTravel. If you want, you could print the TravelURL to see
				// how it really looks like
				//PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}

void UWNoxGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OnDestroySessionComplete %s, %d"), *SessionName.ToString(), bWasSuccessful));

	// Get the OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());
	if (OnlineSub)
	{
		// Get the SessionInterface from the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			// Clear the Delegate
			Sessions->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);

			// If it was successful, we just load another level (could be a MainMenu!)
			if (bWasSuccessful)
			{
				//UGameplayStatics::OpenLevel(GetWorld(), "ThirdPersonExampleMap", true);
				GEngine->HandleDisconnect(GetWorld(), GetWorld()->GetNetDriver());
			}
		}
	}

}

void UWNoxGameInstance::StartOnlineGame()
{
	// Call our custom HostSession function. GameSessionName is a GameInstance variable
	HostSession(GameSessionName, true, true, 4);
}

void UWNoxGameInstance::FindOnlineGames()
{
	FindSessions(true, true);
}

void UWNoxGameInstance::JoinOnlineGame()
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
				JoinSessionCustom(GameSessionName, SearchResult);
				break;
			}
		}
	}
}

void UWNoxGameInstance::DestroySessionAndLeaveGame()
{
	IOnlineSubsystem* OnlineSub = Online::GetSubsystem(GetWorld());
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid())
		{
			Sessions->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(this, &UWNoxGameInstance::OnDestroySessionComplete));

			Sessions->DestroySession(GameSessionName);
		}
	}
}

