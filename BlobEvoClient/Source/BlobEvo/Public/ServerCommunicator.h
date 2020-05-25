// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Sockets.h"

#include "ServerCommunicator.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOBEVO_API AServerCommunicator : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AServerCommunicator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Port;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Ip;

	FSocket* Socket;

	UPROPERTY()
	bool Connected;

	int32 HEADER_SIZE = 3;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	bool Connect();
	
	int32 Recv(FString &Data, int32 NuberOfBytesToRecv, ESocketReceiveFlags::Type Flags);

	virtual int32 Send(FString Data);

	bool HasPendingData(uint32 & PendingDataSize);
};