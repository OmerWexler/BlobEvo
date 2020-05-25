// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerServerCommunicator.h"

void APlayerServerCommunicator::Tick(float DeltaTime)
{
    CheckIncomingLocationReports();
    CheckIncomingPlayerReports();
}

int32 APlayerServerCommunicator::Send(FString Data)
{
    FString Msg = FString(TEXT(""));
    
    if (Data.Len() < 10) {
        Msg += FString(TEXT("0"));
    }

    Msg += FString::FromInt(Data.Len());
    Msg += Data;

    return Super::Send(Msg);
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

        FString X, Y, Z;
        
        X = FString::FromInt(NewVector.X);
        Y = FString::FromInt(NewVector.Y);
        Z = FString::FromInt(NewVector.Z);

        Msg += Super::Wrap(X.Len(), LOCATION_COMPONENET_SIZE_SIZE);
        Msg += Super::Wrap(X, X.Len());

        Msg += Super::Wrap(Y.Len(), LOCATION_COMPONENET_SIZE_SIZE);
        Msg += Super::Wrap(Y, Y.Len());

        Msg += Super::Wrap(Z.Len(), LOCATION_COMPONENET_SIZE_SIZE);
        Msg += Super::Wrap(Z, Z.Len());
        
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
                FString XSize, YSize, ZSize;
                FString PlayerID, X, Y, Z;

                Recv(PlayerID, PLAYER_ID_SIZE, ESocketReceiveFlags::None);
                
                Recv(XSize, LOCATION_COMPONENET_SIZE_SIZE, ESocketReceiveFlags::None);
                Recv(X, FCString::Atoi(*XSize), ESocketReceiveFlags::None);
                
                Recv(YSize, LOCATION_COMPONENET_SIZE_SIZE, ESocketReceiveFlags::None);
                Recv(Y, FCString::Atoi(*YSize), ESocketReceiveFlags::None);
                
                Recv(ZSize, LOCATION_COMPONENET_SIZE_SIZE, ESocketReceiveFlags::None);
                Recv(Z, FCString::Atoi(*ZSize), ESocketReceiveFlags::None);

                FVector NewVector = FVector{
                    FCString::Atof(*X),
                    FCString::Atof(*Y),
                    FCString::Atof(*Z)
                };

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
