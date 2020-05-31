// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerServerCommunicator.h"

void APlayerServerCommunicator::Tick(float DeltaTime)
{
    CheckIncomingLocationReports();
    CheckIncomingPlayerReports();
}

void APlayerServerCommunicator::JoinGame(FString Name, int32 &OutPlayerID)
{
    if (Connected)
    {
        FString Msg = FString(TEXT(""));

        Msg += NEW_PLAYER_REPORT_HEADER;
        Msg += Wrap(Name.Len(), PLAYER_NAME_SIZE_SIZE);
        Msg += Wrap(Name, Name.Len());

        Send(Msg);
        
        FString Header = FString(TEXT(""));
        Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

        if (Header.Equals(PLAYER_ID_HEADER))
        {
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);

            FString NewPlayerID = FString(TEXT(""));
            Recv(NewPlayerID, PLAYER_ID_SIZE, ESocketReceiveFlags::None);

            OutPlayerID = FCString::Atoi(*NewPlayerID);
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
             
                FString ID, Name, NameSize;
                Recv(NameSize, PLAYER_NAME_SIZE_SIZE, ESocketReceiveFlags::None);
                Recv(Name, FCString::Atoi(*NameSize), ESocketReceiveFlags::None);

                LastNewPlayerName = Name;
                bIsNewPlayer = true;
            }
        }
    }
}

bool APlayerServerCommunicator::GetLastNewPlayer(FString& OutPlayerName)
{
    if (bIsNewPlayer)
    {
        bIsNewPlayer = false;
        OutPlayerName = LastNewPlayerName;

        return true;
    }

    return false;
}
