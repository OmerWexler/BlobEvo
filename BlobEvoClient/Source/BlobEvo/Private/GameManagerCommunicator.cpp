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

void AGameManagerCommunicator::ReportGameReady()
{
    if (Connected)
    {
        Send(GAME_READY_HEADER);
    }
}

bool AGameManagerCommunicator::CheckIfGameReady()
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);
            
            if (Header.Equals(GAME_READY_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                return true;
            }
        }
    }

    return false;
}

void AGameManagerCommunicator::ReportStartOfBlobStream()
{
    if (Connected)
    {
        Send(START_BLOB_SPAWN_STREAM_HEADER);
    }
}

bool AGameManagerCommunicator::CheckIfBlobStreamStarted()
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);
            
            if (Header.Equals(START_BLOB_SPAWN_STREAM_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                return true;
            }
        }
    }

    return false;
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
                
                FString BlobIDSize, PlayerIDS;

                Recv(BlobIDSize, Super::BLOB_ID_SIZE_SIZE, ESocketReceiveFlags::None);
                Recv(BlobID, FCString::Atoi(*BlobIDSize), ESocketReceiveFlags::None);
                
                Recv(PlayerIDS, Super::PLAYER_ID_SIZE, ESocketReceiveFlags::None);
                PlayerID = FCString::Atoi(*PlayerIDS);

                RecvVector(SpawnLocation);

                return true;
            }
        }
    }

    return false;
}

void AGameManagerCommunicator::ReportEndOfBlobStream()
{
    if (Connected)
    {
        Send(END_BLOB_SPAWN_STREAM_HEADER);
    }
}

bool AGameManagerCommunicator::CheckIfBlobStreamEnded()
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(END_BLOB_SPAWN_STREAM_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
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
