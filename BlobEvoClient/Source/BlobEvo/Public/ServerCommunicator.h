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

	int32 PLAYER_ID_SIZE = 2;
	int32 BLOB_ID_SIZE_SIZE = 1;

	int32 HEADER_SIZE = 3;
	int32 VECTOR_COMPONENT_SIZE_SIZE = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	bool Connect();

	int32 Recv(FString &Data, int32 NuberOfBytesToRecv, ESocketReceiveFlags::Type Flags);

	virtual int32 Send(FString Data);

	bool HasPendingData(uint32 & PendingDataSize);

	void RecvVector(FVector& OutVector);
	FString Wrap(FVector Value);
	FString Wrap(int32 Value, int32 ToSize);
	FString Wrap(float Value, int32 ToSize);
	FString Wrap(FString Value, int32 ToSize);
};