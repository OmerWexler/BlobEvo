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

	UFUNCTION(BlueprintCallable)
	void JoinGame(FString Name, int32 &OutPlayerID);

	UFUNCTION(BlueprintCallable)
	void ReportNewLocation(int32 PlayerID, FVector NewVector);

	UFUNCTION(BlueprintCallable)
	bool CheckForNewLocation(int32 ID, FVector& OutVector);

	UFUNCTION(BlueprintCallable)
	bool GetLastNewPlayer(FString& OutPlayerName);

private:
	int32 PLAYER_ID_SIZE = 2;
	int32 PLAYER_NAME_SIZE_SIZE = 2;

	FString NEW_PLAYER_REPORT_HEADER = FString(TEXT("RNP"));
	FString NEW_LOCATION_REPORT_HEADER = FString(TEXT("RNL"));
	FString PLAYER_ID_HEADER = FString(TEXT("PIH"));

	TMap<int32, FVector> StoredLocations;
	
	bool bIsNewPlayer = false;
	FString LastNewPlayerName;

	void CheckIncomingLocationReports();
	void CheckIncomingPlayerReports();
};
