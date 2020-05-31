// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServerCommunicator.h"
#include "BlobDirectionCommunicator.generated.h"

/**
 * 
 */
UCLASS()
class BLOBEVO_API ABlobDirectionCommunicator : public AServerCommunicator
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// UFUNCTION(BlueprintCallable)
	// void ReportNewBlobDirection(FString BlobID, int32 NewDirection);	
	
	// UFUNCTION(BlueprintCallable)
	// bool CheckForNewBlobDirection(FString BlobID, int32& OutDirection);
	

	UFUNCTION(BlueprintCallable)
	void ReportNewBlobDirection(FString BlobID, FTransform NewTransform);	
	
	UFUNCTION(BlueprintCallable)
	bool CheckForNewBlobDirection(FString BlobID, FTransform& NewTransform);
	
private:
	int32 BLOB_DIRECTION_SIZE = 5;
	FString DIRECTION_REPORT_HEADER = FString(TEXT("RBD"));

	UPROPERTY(EditAnywhere)
	TMap<FString, FTransform> StoredBlobDirections;

	void CheckPendingReports();
};
