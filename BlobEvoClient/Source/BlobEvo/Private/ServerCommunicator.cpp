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

	if (Connected)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is connected to %i.%i.%i.%i at port %i."), *GetOwner()->GetName(), Ip[0], Ip[1], Ip[2], Ip[3], Port);
	}

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

		UE_LOG(LogTemp, Warning, TEXT("%s received %i bytes: %s from server."), *GetOwner()->GetName(), BytesReceived, *Data);

		delete Buffer;
		return BytesReceived;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Unable to recv until connected to server."), *GetOwner()->GetName());
	}
	return 0;
}

int32 UServerCommunicator::Send(FString Data)
{
	if (Connected)
	{
		uint8* Buffer = new uint8[Data.Len()];
		int32 BytesSent;
		StringToBytes(Data, Buffer, Data.Len());

		Socket->Send(Buffer, 4, BytesSent);
		UE_LOG(LogTemp, Warning, TEXT("%s sent %i bytes: %s to server."), *GetOwner()->GetName(), BytesSent, *Data);

		delete Buffer;
		return BytesSent;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Unable to send until connected to server."), *GetOwner()->GetName());
	}
	return 0;
}