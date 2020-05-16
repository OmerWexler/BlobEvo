// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Spawner.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	if (ParentSpawner) 
	{
		Cast<ASpawner>(ParentSpawner)->AddSpawnVolume(this);
	} 
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Must pick parent spawner on %s"), *GetName());
	}
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnVolume::GetRandomSpawnLocation(FVector &OutLocation) const
{
	FVector SpawningBoundryOrigin;
	FVector SpawningBoundryExtent;

	GetActorBounds(false, SpawningBoundryOrigin, SpawningBoundryExtent, true);
	
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
}