// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerServerCommunicator.h"

void APlayerServerCommunicator::Tick(float DeltaTime)
{

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
        Send(REPORT_HEADER);

        // FString Header = FString(TEXT(""));
        // Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);

        // if (Header.Equals(PLAYER_COUNT_HEADER))
        // {
        //     FString PlayerCount = FString(TEXT(""));
        //     Recv(PlayerCount, PLAYER_COUNT_SIZE, ESocketReceiveFlags::None);

        //     OutPlayerCount = FCString::Atoi(*PlayerCount);
        // }
    }
}