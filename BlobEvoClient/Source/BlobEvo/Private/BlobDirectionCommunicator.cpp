// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobDirectionCommunicator.h"

// Called when the game starts
void ABlobDirectionCommunicator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlobDirectionCommunicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (Connected) {
        CheckPendingReports();
    }
}

// void ABlobDirectionCommunicator::ReportNewBlobDirection(FString BlobID, int32 NewDirection)
// {
//     FString Msg = FString(TEXT(""));
//     Msg += DIRECTION_REPORT_HEADER;
    
//     Msg += Wrap(BlobID.Len(), Super::BLOB_ID_SIZE_SIZE);
//     Msg += Wrap(BlobID, BlobID.Len());
//     Msg += Wrap(NewDirection, 4);

//     Send(Msg);
// }

// bool ABlobDirectionCommunicator::CheckForNewBlobDirection(FString BlobID, int32& OutDirection)
// {
//     if (StoredBlobDirections.Contains(BlobID)) 
//     {
//         OutDirection = StoredBlobDirections[BlobID];
//         StoredBlobDirections.Remove(BlobID);
//         return true;
//     }
//     else 
//     {
//         return false;
//     }
// }

// void ABlobDirectionCommunicator::CheckPendingReports()
// {
//     if (Connected)
//     {
//         uint32 PendingData; 
//         if (HasPendingData(PendingData))
//         {
//             FString Header;
//             Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

//             if (Header.Equals(DIRECTION_REPORT_HEADER, ESearchCase::IgnoreCase))
//             {
//                 Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);

//                 FString BLOB_ID_SIZE, BlobID, Direction;
//                 FTransform Transform;

//                 Recv(BLOB_ID_SIZE, Super::BLOB_ID_SIZE_SIZE, ESocketReceiveFlags::None);
//                 Recv(BlobID, FCString::Atoi(*BLOB_ID_SIZE), ESocketReceiveFlags::None);
//                 Recv(Direction, 4, ESocketReceiveFlags::None);

                
//                 StoredBlobDirections.Add(BlobID, FCString::Atoi(*Direction));
//             }
//         }
//     }
// }

void ABlobDirectionCommunicator::ReportNewBlobDirection(FString BlobID, FTransform NewTransform)
{
    FString Msg = FString(TEXT(""));
    Msg += DIRECTION_REPORT_HEADER;
    
    Msg += Wrap(BlobID.Len(), Super::BLOB_ID_SIZE_SIZE);
    Msg += Wrap(BlobID, BlobID.Len());
    Msg += Wrap(NewTransform);

    Send(Msg);
}

bool ABlobDirectionCommunicator::CheckForNewBlobDirection(FString BlobID, FTransform& OutTransform)
{
    if (StoredBlobDirections.Contains(BlobID)) 
    {
        OutTransform = StoredBlobDirections[BlobID];
        StoredBlobDirections.Remove(BlobID);
        return true;
    }
    else 
    {
        return false;
    }
}

void ABlobDirectionCommunicator::CheckPendingReports()
{
    if (Connected)
    {
        uint32 PendingData; 
        if (HasPendingData(PendingData))
        {
            FString Header;
            Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::Peek);

            if (Header.Equals(DIRECTION_REPORT_HEADER, ESearchCase::IgnoreCase))
            {
                Recv(Header, Super::HEADER_SIZE, ESocketReceiveFlags::None);

                FString BLOB_ID_SIZE, BlobID, Direction;
                FTransform Transform;

                Recv(BLOB_ID_SIZE, Super::BLOB_ID_SIZE_SIZE, ESocketReceiveFlags::None);
                Recv(BlobID, FCString::Atoi(*BLOB_ID_SIZE), ESocketReceiveFlags::None);
                
                RecvTransform(Transform);
                
                StoredBlobDirections.Add(BlobID, Transform);
            }
        }
    }
}