// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerServerCommunicator.h"

void APlayerServerCommunicator::Tick(float DeltaTime)
{
    CheckIncomingLocationReports();
    CheckIncomingPlayerReports();
}

void APlayerServerCommunicator::JoinGame(int32& OutPlayerCount)
{
    if (Connected)
    {
        Send(NEW_PLAYER_REPORT_HEADER);

        FString Header = FString(TEXT(""));
        Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

        if (Header.Equals(PLAYER_COUNT_HEADER))
        {
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);

            FString PlayerCount = FString(TEXT(""));
            Recv(PlayerCount, PLAYER_COUNT_SIZE, ESocketReceiveFlags::None);

            OutPlayerCount = FCString::Atoi(*PlayerCount);
        }
    }
}

void APlayerServerCommunicator::ReportNewLocation(int32 PlayerID, FVector NewVector)
{
    if (Connected)
    {   
        FString Msg = FString(TEXT("")) + NEW_LOCATION_REPORT_HEADER;
        
        Msg += Super::Wrap(PlayerID, PLAYER_ID_SIZE);
        Msg += Super::Wrap(NewVector);
        
        Send(Msg);
    }
}

void APlayerServerCommunicator::CheckIncomingLocationReports()
{
    if (Connected)
    {   
        uint32 PendingDataSize;
        if (HasPendingData(PendingDataSize))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(NEW_LOCATION_REPORT_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                
                FString PlayerID;
	            Recv(PlayerID, PLAYER_ID_SIZE, ESocketReceiveFlags::None);
                
                FVector NewVector;
                Super::RecvVector(NewVector);
                
                UE_LOG(LogTemp, Warning, TEXT("Received vector \"%s\" to puppet \"%i\""), *NewVector.ToString(), FCString::Atoi(*PlayerID));

                StoredLocations.Add(FCString::Atoi(*PlayerID), NewVector);
            }
        }
    }
}

bool APlayerServerCommunicator::CheckForNewLocation(int32 ID, FVector& OutLocation)
{
    if (StoredLocations.Contains(ID)) 
    {
        OutLocation = StoredLocations[ID];
        return true;
    }
    else 
    {
        return false;
    }
}

void APlayerServerCommunicator::CheckIncomingPlayerReports()
{
    if (Connected)
    {   
        uint32 PendingDataSize;
        if (HasPendingData(PendingDataSize))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(NEW_PLAYER_REPORT_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);
                UE_LOG(LogTemp, Warning, TEXT("A new player has joined"));

                NewPlayers ++;
            }
        }
    }
}

int32 APlayerServerCommunicator::GetNewPlayerCount()
{
    return NewPlayers;
}

void APlayerServerCommunicator::PopPlayer()
{
    NewPlayers--;
}
