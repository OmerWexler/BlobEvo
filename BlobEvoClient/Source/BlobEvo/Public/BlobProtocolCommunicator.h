// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerCommunicator.h"
#include "BlobProtocolCommunicator.generated.h"

/**
 * 
 */
UCLASS()
class BLOBEVO_API ABlobProtocolCommunicator : public AServerCommunicator
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	bool CheckForNewBLobDirection(int32 BlobID, int32& OutDirection);
	
	UFUNCTION(BlueprintCallable)
	void ReportNewBLobDirection(int32 BlobID, int32 NewDirection);
	
	// Only called on client.
	UFUNCTION(BlueprintCallable)
	void EnablePeriodicReportChecks(bool Enabled);

private:
	int32 BLOB_ID_SIZE = 4;
	int32 BLOB_DIRECTION_SIZE = 3;
	FString REPORT_HEADER = FString(TEXT("REP"));

	TMap<int32, int32> StoredBlobDirections;

	bool ArePeriodicChecksEnabled = false;	
	void CheckPendingReports();
};
