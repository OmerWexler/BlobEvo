// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerCommunicator.h"
#include "PlayerServerCommunicator.generated.h"

/**
 * 
 */
UCLASS()
class BLOBEVO_API APlayerServerCommunicator : public AServerCommunicator
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	int32 Send(FString Data) override;

	UFUNCTION(BlueprintCallable)
	void JoinGame(int32& OutPlayerCount);

	UFUNCTION(BlueprintCallable)
	void ReportNewLocation(int32 PlayerID, FVector NewVector);

	UFUNCTION(BlueprintCallable)
	bool CheckForNewLocation(int32 ID, FVector& OutVector);

	UFUNCTION(BlueprintCallable)
	int32 GetNewPlayerCount();

	UFUNCTION(BlueprintCallable)
	void PopPlayer();

private:
	int32 PLAYER_COUNT_SIZE = 2;
	int32 PLAYER_ID_SIZE = 2;
	int32 LOCATION_COMPONENET_SIZE_SIZE = 1;

	int32 NewPlayers = 0;
	
	FString NEW_PLAYER_REPORT_HEADER = FString(TEXT("RNP"));
	FString NEW_LOCATION_REPORT_HEADER = FString(TEXT("RNL"));
	FString PLAYER_COUNT_HEADER = FString(TEXT("PCH"));

	TMap<int32, FVector> StoredLocations;

	void CheckIncomingLocationReports();
	void CheckIncomingPlayerReports();
};
