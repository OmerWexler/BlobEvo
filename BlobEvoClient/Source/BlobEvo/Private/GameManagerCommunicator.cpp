// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerCommunicator.h"
#include "SocketTypes.h"

// Called when the game starts
void AGameManagerCommunicator::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGameManagerCommunicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameManagerCommunicator::ReportBlobSpawn(FString BlobID, int32 PlayerID, FVector SpawnLocation)
{
    if (Connected)
    {
        FString Msg = FString(TEXT(""));
        Msg += BLOB_SPAWN_HEADER;

        Msg += Super::Wrap(BlobID.Len(), Super::BLOB_ID_SIZE_SIZE);
        Msg += Super::Wrap(BlobID, BlobID.Len());

        Msg += Super::Wrap(PlayerID, Super::PLAYER_ID_SIZE);
        Msg += Super::Wrap(SpawnLocation);

        Send(Msg);
    }
}

bool AGameManagerCommunicator::ReceiveBlobSpawn(FString& BlobID, int32& PlayerID, FVector& SpawnLocation)
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(BLOB_SPAWN_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                
                FString BlobIDSize, BlobIDS, PlayerIDS;

                Recv(BlobIDSize, Super::BLOB_ID_SIZE_SIZE, ESocketReceiveFlags::None);
                Recv(BlobIDS, FCString::Atoi(*BlobIDSize), ESocketReceiveFlags::None);
                
                Recv(PlayerIDS, Super::PLAYER_ID_SIZE, ESocketReceiveFlags::None);
                
                PlayerID = FCString::Atoi(*PlayerIDS);
                BlobID = FString(TEXT("")) + BlobIDS;

                RecvVector(SpawnLocation);

                return true;
            }
        }
    }

    return false;
}

void AGameManagerCommunicator::ReportDonutSpawn(FVector SpawnLocation)
{
    if (Connected)
    {
        FString Msg = FString(TEXT(""));
        Msg += DONUT_SPAWN_HEADER;
        Msg += Super::Wrap(SpawnLocation);

        Send(Msg);
    }
}

bool AGameManagerCommunicator::ReceiveDonutSpawn(FVector& SpawnLocation)
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(DONUT_SPAWN_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                RecvVector(SpawnLocation);

                return true;
            }
        }
    }

    return false;
}

void AGameManagerCommunicator::ReportBeginRound()
{
    if (Connected)
    {
        Send(BEGIN_ROUND_HEADER);
    }
}

bool AGameManagerCommunicator::CheckIfRoundBegan()
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(BEGIN_ROUND_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                return true;
            }
        }
    }

    return false;
}

void AGameManagerCommunicator::ReportRoundEnd()
{    
    if (Connected)
    {
        Send(END_ROUND_HEADER);
    }
}

bool AGameManagerCommunicator::CheckIfRoundEnded()
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(END_ROUND_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                return true;
            }
        }
    }

    return false;
}