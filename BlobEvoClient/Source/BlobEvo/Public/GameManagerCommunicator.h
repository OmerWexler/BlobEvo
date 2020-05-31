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

	/* Blob Spawns */
	UFUNCTION(BlueprintCallable)
	void ReportBlobSpawn(FString BlobID, int32 PlayerID, FVector SpawnLocation);
	
	UFUNCTION(BlueprintCallable)
	bool ReceiveBlobSpawn(FString& BlobID, int32& PlayerID, FVector& SpawnLocation);
	/* Blob Spawns */

	/* Donut Spawns */
	UFUNCTION(BlueprintCallable)
	void ReportDonutSpawn(FVector SpawnLocation);
	
	UFUNCTION(BlueprintCallable)
	bool ReceiveDonutSpawn(FVector& SpawnLocation);
	/* Donut Spawns */
	
	/* Begin Round */
	UFUNCTION(BlueprintCallable)
	void ReportBeginRound();
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfRoundBegan();
	/* Begin Round */

	/* End Round */
	UFUNCTION(BlueprintCallable)
	void ReportRoundEnd();
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfRoundEnded();
	/* End Round */

private:
	FString START_BLOB_SPAWN_STREAM_HEADER = FString(TEXT("SBS"));
	FString BLOB_SPAWN_HEADER = FString(TEXT("RBS"));
	FString END_BLOB_SPAWN_STREAM_HEADER = FString(TEXT("EBS"));

	FString START_DONUT_SPAWN_STREAM_HEADER = FString(TEXT("SDS"));
	FString DONUT_SPAWN_HEADER = FString(TEXT("RDS"));
	FString END_DONUT_SPAWN_STREAM_HEADER = FString(TEXT("EDS"));
	
	FString BEGIN_ROUND_HEADER = FString(TEXT("RBR"));
	FString END_ROUND_HEADER = FString(TEXT("RER"));
};
