// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerCommunicator.h"

#include "HAL/Platform.h"
#include "Containers/UnrealString.h"
#include "SocketTypes.h"

// Sets default values for this component's properties
AServerCommunicator::AServerCommunicator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void AServerCommunicator::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AServerCommunicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ...
}

bool AServerCommunicator::Connect()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address Ipv4(Ip[0], Ip[1], Ip[2], Ip[3]);
	Addr->SetIp(Ipv4.Value);
	Addr->SetPort(Port);

	Connected = Socket->Connect(*Addr);

	// if (Connected)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s is connected to %i.%i.%i.%i at port %i."), *GetName(), Ip[0], Ip[1], Ip[2], Ip[3], Port);
	// }

	return Connected;
}

int32 AServerCommunicator::Recv(FString &Data, int32 NuberOfBytesToRecv, ESocketReceiveFlags::Type Flags)
{
	if (Connected)
	{
		int32 BytesReceived;
		uint8* Buffer = new uint8[NuberOfBytesToRecv];

		Socket->Recv(Buffer, NuberOfBytesToRecv, BytesReceived, Flags);
		Data += BytesToString(Buffer, NuberOfBytesToRecv);

		// UE_LOG(LogTemp, Warning, TEXT("%s received %i bytes: %s from server."), *GetName(), BytesReceived, *Data);

		delete Buffer;
		return BytesReceived;
	}
	// else 
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s Unable to recv until connected to server."), *GetName());
	// }
	return 0;
}

int32 AServerCommunicator::Send(FString Data)
{
	if (Connected)
	{
		Data = Wrap(Data.Len(), 2) + Data;
		
		uint8* Buffer = new uint8[Data.Len()];
		int32 BytesSent;

		StringToBytes(Data, Buffer, Data.Len());

		Socket->Send(Buffer, Data.Len(), BytesSent);
		// UE_LOG(LogTemp, Warning, TEXT("%s sent %i bytes: %s to server."), *GetName(), BytesSent, *Data);

		delete Buffer;
		return BytesSent;
	}
	// else 
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%s Unable to send until connected to server."), *GetName());
	// }
	return 0;
}

bool AServerCommunicator::HasPendingData(uint32& PendingDataSize) 
{
	if (Connected) 
	{
		return Socket->HasPendingData(PendingDataSize);
	}
	else
	{
		return false;
	}
	
}

void AServerCommunicator::RecvTransform(FTransform& OutTransform)
{
	OutTransform = FTransform();
	FVector Translation;
	RecvVector(Translation);

	FString Yaw, YawSize;
	Recv(YawSize, VECTOR_COMPONENT_SIZE_SIZE, ESocketReceiveFlags::None);
	Recv(Yaw, FCString::Atoi(*YawSize), ESocketReceiveFlags::None);

	OutTransform.SetTranslation(Translation);
	OutTransform.SetRotation(FQuat(FRotator(0.0, FCString::Atof(*Yaw), 0.0)));
}

FString AServerCommunicator::Wrap(FTransform Value){
	FString AsMsg = FString(TEXT(""));

	AsMsg += Wrap(Value.GetLocation());

	FString Yaw = FString::SanitizeFloat(Value.Rotator().Yaw);

	AsMsg += Wrap(Yaw.Len(), VECTOR_COMPONENT_SIZE_SIZE);
	AsMsg += Wrap(Yaw, Yaw.Len());

	return AsMsg;
}

void AServerCommunicator::RecvVector(FVector& OutVector)
{
	FString XSize, YSize, ZSize;
	FString PlayerID, X, Y, Z;
	
	Recv(XSize, VECTOR_COMPONENT_SIZE_SIZE, ESocketReceiveFlags::None);
	Recv(X, FCString::Atoi(*XSize), ESocketReceiveFlags::None);
	
	Recv(YSize, VECTOR_COMPONENT_SIZE_SIZE, ESocketReceiveFlags::None);
	Recv(Y, FCString::Atoi(*YSize), ESocketReceiveFlags::None);
	
	Recv(ZSize, VECTOR_COMPONENT_SIZE_SIZE, ESocketReceiveFlags::None);
	Recv(Z, FCString::Atoi(*ZSize), ESocketReceiveFlags::None);

	OutVector.X = FCString::Atof(*X);
	OutVector.Y = FCString::Atof(*Y);
	OutVector.Z = FCString::Atof(*Z);
}

FString AServerCommunicator::Wrap(FVector Value)
{
	FString AsMsg = FString(TEXT(""));

	FString X = FString::SanitizeFloat(Value.X);
	FString Y = FString::SanitizeFloat(Value.Y);
	FString Z = FString::SanitizeFloat(Value.Z);

	AsMsg += Wrap(X.Len(), VECTOR_COMPONENT_SIZE_SIZE);
	AsMsg += Wrap(X, X.Len());

	AsMsg += Wrap(Y.Len(), VECTOR_COMPONENT_SIZE_SIZE);
	AsMsg += Wrap(Y, Y.Len());

	AsMsg += Wrap(Z.Len(), VECTOR_COMPONENT_SIZE_SIZE);
	AsMsg += Wrap(Z, Z.Len());

	return AsMsg;
}

FString AServerCommunicator::Wrap(int32 Value, int32 ToSize)
{
	return Wrap(FString::FromInt(Value), ToSize);
}

FString AServerCommunicator::Wrap(float Value, int32 ToSize)
{
	return Wrap(FString::SanitizeFloat(Value), ToSize);
}

FString AServerCommunicator::Wrap(FString Value, int32 ToSize)
{
	FString AsFString = Value;

	if (AsFString.Len() > ToSize)
	{
		TArray<TCHAR> AsChars = AsFString.GetCharArray();
		AsFString = FString(TEXT(""));
		
		for (int i = 0; i < ToSize; i++) 
		{
			AsFString += AsChars[i];
		}
	}
	
	else if (AsFString.Len() < ToSize)
	{
		while (AsFString.Len() < ToSize) 
		{
			AsFString = FString(TEXT("0")) + AsFString;
		}
	}

	return AsFString;
}