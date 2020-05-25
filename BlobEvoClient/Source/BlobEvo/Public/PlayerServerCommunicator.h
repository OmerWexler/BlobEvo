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

private:
	int32 PLAYER_COUNT_SIZE = 2;
	FString REPORT_HEADER = FString((TEXT("RNP")));
	FString PLAYER_COUNT_HEADER = FString((TEXT("PCH")));
};
