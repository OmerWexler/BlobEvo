// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketTypes.h"
#include "Misc/CString.h"

#include "BlobProtocolCommunicator.h"

// Called when the game starts
void ABlobProtocolCommunicator::BeginPlay()
{
	Super::BeginPlay();
    EnablePeriodicReportChecks(true);
}


// Called every frame
void ABlobProtocolCommunicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (ArePeriodicChecksEnabled) 
    {
        if (Connected) {
            CheckPendingReports();
        }
    }
}

bool ABlobProtocolCommunicator::CheckForNewBLobDirection(int32 BlobID, int32& OutDirection)
{
    if (StoredBlobDirections.Contains(BlobID)) 
    {
        OutDirection = StoredBlobDirections[BlobID];
        return true;
    }
    else 
    {
        return false;
    }
}

void ABlobProtocolCommunicator::ReportNewBLobDirection(int32 BlobID, int32 NewDirection)
{
    if (BlobID > 1000) return;
    if (NewDirection > 360) return;

    FString Msg = FString(TEXT(""));
    Msg += REPORT_HEADER;
    
    if (BlobID < 1000) 
    {
        Msg += FString(TEXT("0"));
        if (BlobID < 100) 
        {
            Msg += FString(TEXT("0"));
            if (BlobID < 10)
            {
                Msg += FString(TEXT("0"));
            } 
        }
    }
    Msg += FString::FromInt(BlobID);

    if (NewDirection < 100)
    {
        Msg += FString(TEXT("0"));
        if (NewDirection < 10)
        {
            Msg += FString(TEXT("0"));
        }
    }
    Msg += FString::FromInt(NewDirection);
    Send(Msg);
}

void ABlobProtocolCommunicator::EnablePeriodicReportChecks(bool Enabled)
{
    ArePeriodicChecksEnabled = Enabled;
}

void ABlobProtocolCommunicator::CheckPendingReports()
{
    uint32 PendingData; 
    if (HasPendingData(PendingData))
    {
        FString Header;
        Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);

        if (Header.Equals(REPORT_HEADER, ESearchCase::IgnoreCase))
        {
            FString BlobID, Direction;
            Recv(BlobID, BLOB_ID_SIZE, ESocketReceiveFlags::None);
            Recv(Direction, BLOB_DIRECTION_SIZE, ESocketReceiveFlags::None);
            
            UE_LOG(LogTemp, Warning, TEXT("Added direction \"%i\" to blob \"%i\""), FCString::Atoi(*Direction), FCString::Atoi(*BlobID));
            StoredBlobDirections.Add(FCString::Atoi(*BlobID), FCString::Atoi(*Direction));
        }
    }
}