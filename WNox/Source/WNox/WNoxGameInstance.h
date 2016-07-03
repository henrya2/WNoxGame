#pragma once

#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "WNoxGameInstance.generated.h"

class FOnlineSessionSearchResult;

UCLASS(Blueprintable)
class UWNoxGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UWNoxGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	class UItemInfoManager* GetItemInfoManager() const { return ItemInfoManager; }

	virtual void Init() override;

	/**
	*  Function to host a game!
	*
	*  @Param    SessionName    Name of the Session
	*  @Param    bIsLAN      Is this is LAN Game?
	*  @Param    bIsPresence    "Is the Session to create a presence Session"
	*  @Param    MaxNumPlayers          Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostSession(FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	/**
	*  Function fired when a session create request has completed
	*
	*  @param SessionName the name of the session this callback is for
	*  @param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	/**
	*  Function fired when a session start request has completed
	*
	*  @param SessionName the name of the session this callback is for
	*  @param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	/**
	*  Find an online session
	*
	*  @param UserId user that initiated the request
	*  @param bIsLAN are we searching LAN matches
	*  @param bIsPresence are we searching presence sessions
	*/
	void FindSessions(bool bIsLAN, bool bIsPresence);

	/**
	*  Delegate fired when a session search query has completed
	*
	*  @param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnFindSessionsComplete(bool bWasSuccessful);

	/**
	*	Joins a session via a search result
	*
	*	@param SessionName name of session
	*	@param SearchResult Session to join
	*
	*	@return bool true if successful, false otherwise
	*/
	bool JoinSessionCustom(FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	/**
	*	Delegate fired when a session join request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/**
	*	Delegate fired when a destroying an online session has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	// Blueprint functions

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void StartOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void FindOnlineGames();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void JoinOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void DestroySessionAndLeaveGame();

protected:
	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "DataTable")
	class UItemInfoManager* ItemInfoManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	class UDataTable* ItemInfoDataTable;
};
