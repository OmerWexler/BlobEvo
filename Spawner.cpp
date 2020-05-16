// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Engine/World.h"
#include "Containers/Array.h"


// Sets default values for this component's properties
USpawner::USpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawner::BeginPlay()
{
	Super::BeginPlay();
}

void USpawner::GenerateRandomSpawningLocation(FVector& OutLocation) {
	int32 SpawnBoundryIndex = FMath::RandRange(0, SpawnBoundries.Num() - 1);
	
	FVector SpawningBoundryOrigin;
	FVector SpawningBoundryExtent;
	bool bIsOvelappingOverBlob = false;
	
	do {
		bIsOvelappingOverBlob = false;
		
		SpawnBoundries[SpawnBoundryIndex]->GetActorBounds(false, SpawningBoundryOrigin, SpawningBoundryExtent);
		
		OutLocation.X = FMath::RandRange(
			SpawningBoundryOrigin.X - SpawningBoundryExtent.X, 
			SpawningBoundryOrigin.X + SpawningBoundryExtent.X
		);

		OutLocation.Y = FMath::RandRange(
			SpawningBoundryOrigin.Y - SpawningBoundryExtent.Y, 
			SpawningBoundryOrigin.Y + SpawningBoundryExtent.Y
		);

		OutLocation.Z = FMath::RandRange(
			SpawningBoundryOrigin.Z - SpawningBoundryExtent.Z, 
			SpawningBoundryOrigin.Z + SpawningBoundryExtent.Z
		);

		for (int32 i = 0; i < Blobs.Num(); i ++) {
			if (FVector::Distance(OutLocation, Blobs[i]->GetTransform().GetTranslation()) < SpawnSpacing) {
				bIsOvelappingOverBlob = true;
				break;
			}
		}
	} while (bIsOvelappingOverBlob);
}

void USpawner::SpawnBlobCount(int32 BlobCount) {
	
	if (BlobClass) {
		UWorld* world = GetWorld();

		if (world) {
			for (int32 i = 0; i < BlobCount; i++) {
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = GetOwner();

				FVector location;
				GenerateRandomSpawningLocation(location);
				UE_LOG(LogTemp, Warning, TEXT("Location %s"), *location.ToString());
				FRotator rotation = FRotator(0, 0, 0);

				AActor* NewBlob = world->SpawnActor<AActor>(BlobClass, location, rotation, spawnParams);
				
				Blobs.Add(NewBlob);
			}
		} 
	}
}

// Called every frame
void USpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

