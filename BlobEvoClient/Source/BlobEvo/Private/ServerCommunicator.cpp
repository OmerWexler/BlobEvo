// Fill out your copyright notice in the Description page of Project Settings.

#include "HAL/Platform.h"
#include "Containers/UnrealString.h"
#include "SocketTypes.h"

#include "ServerCommunicator.h"

// Sets default values for this component's properties
UServerCommunicator::UServerCommunicator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UServerCommunicator::BeginPlay()
{
	Super::BeginPlay();

	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address Ipv4(Ip[0], Ip[1], Ip[2], Ip[3]);
	Addr->SetIp(Ipv4.Value);
	Addr->SetPort(Port);

	bool connected = Socket->Connect(*Addr);
	if (connected) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Connected"));
		
		uint8* Data = new uint8[4];
		int32 Bytes;
		StringToBytes(FString(TEXT("BBBB")), Data, 4);

		if (Data) 
		{
			Socket->Send(Data, 4, Bytes);
			UE_LOG(LogTemp, Warning, TEXT("Sent %i bytes"), Bytes);
		}

		FString Received;
		Recv(Received, 4, ESocketReceiveFlags::WaitAll);
		// Socket->Recv(Data, 4, Bytes, ESocketReceiveFlags::WaitAll);

		// if (Data) 
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("Received %i bytes: %s"), Bytes, *BytesToString(Data, 4));
		// }


		delete Data;
	}
	// ...
	
}


// Called every frame
void UServerCommunicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UServerCommunicator::Connect()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address Ipv4(Ip[0], Ip[1], Ip[2], Ip[3]);
	Addr->SetIp(Ipv4.Value);
	Addr->SetPort(Port);

	Connected = Socket->Connect(*Addr);
	return Connected;
}

int32 UServerCommunicator::Recv(FString Data, int32 NuberOfBytesToRecv, ESocketReceiveFlags::Type Flags)
{
	if (Connected)
	{
		int32 BytesReceived;
		uint8* Buffer = new uint8[NuberOfBytesToRecv];

		Socket->Recv(Buffer, NuberOfBytesToRecv, BytesReceived, Flags);
		Data = BytesToString(Buffer, NuberOfBytesToRecv);

		UE_LOG(LogTemp, Warning, TEXT("Received %i bytes: %s"), BytesReceived, *Data);

		delete Buffer;
		return BytesReceived;
	}
	else 
	{
		
	}
	return 0;
}

int32 UServerCommunicator::Send(FString Data)
{
	if (Connected)
	{

	}
	else 
	{
		
	}
	return 0;
}