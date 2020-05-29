// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerCommunicator.h"
#include "GameManagerCommunicator.generated.h"

/**
 * 
 */
UCLASS()
class BLOBEVO_API AGameManagerCommunicator : public AServerCommunicator
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/* Game Ready */
	UFUNCTION(BlueprintCallable)
	void ReportGameReady();
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfGameReady();
	/* Game Ready */
	
	/* Blob Spawns */
	UFUNCTION(BlueprintCallable)
	void ReportStartOfBlobStream();
	
	UFUNCTION(BlueprintCallable)
	void ReportBlobSpawn(FString BlobID, int32 PlayerID, FVector SpawnLocation);
	
	UFUNCTION(BlueprintCallable)
	bool ReceiveBlobSpawn(FString& BlobID, int32& PlayerID, FVector& SpawnLocation);
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfBlobStreamStarted();
	
	UFUNCTION(BlueprintCallable)
	void ReportEndOfBlobStream();

	UFUNCTION(BlueprintCallable)
	bool CheckIfBlobStreamEnded();
	/* Blob Spawns */

	/* Begin Round */
	UFUNCTION(BlueprintCallable)
	void ReportBeginRound();
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfRoundBegan();
	/* Begin Round */

private:
	FString GAME_READY_HEADER = FString(TEXT("RGR"));

	FString START_BLOB_SPAWN_STREAM_HEADER = FString(TEXT("SBS"));
	FString BLOB_SPAWN_HEADER = FString(TEXT("RBS"));
	FString END_BLOB_SPAWN_STREAM_HEADER = FString(TEXT("EBS"));
	
	FString BEGIN_ROUND_HEADER = FString(TEXT("RBG"));
};
