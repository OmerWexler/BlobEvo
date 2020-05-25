// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Engine/World.h"
#include "SpawnVolume.h"
#include "Containers/Array.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnVolumes = TArray<AActor*>();
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASpawner::GenerateRandomSpawningLocation(FVector& OutLocation) 
{
	FVector SpawningBoundryOrigin;
	FVector SpawningBoundryExtent;
	ASpawnVolume* CurrentSpawnVolume = nullptr;

	bool bIsLocationValid = false;
	
	do 
	{
		if (SpawnVolumes.Num() > 0) 
		{
			CurrentSpawnVolume = Cast<ASpawnVolume>(SpawnVolumes[FMath::RandRange(0, SpawnVolumes.Num() - 1)]);
		}
		if (CurrentSpawnVolume) 
		{
			CurrentSpawnVolume->GetRandomSpawnLocation(OutLocation);
		} 
		else 
		{
			OutLocation = FVector();
		}

		for (int32 i = 0; i < Spawns.Num(); i ++) 
		{
			if (FVector::Distance(OutLocation, Spawns[i]->GetTransform().GetTranslation()) > SpawnSpacing) 
			{
				bIsLocationValid = true;
				break;
			}
		}
	} while (false);
}

TArray<AActor*> ASpawner::SpawnByCount(int32 Count, TSubclassOf<AActor> ClassToSpawn) 
{
	bool bActorIsOnSpawner;
	FActorSpawnParameters spawnParams;
	Spawns = TArray<AActor*>();

	if (ClassToSpawn) 
	{
		UWorld* World = GetWorld();

		if (World) {
			for (int32 i = 0; i < Count; i++) 
			{
				FVector Location;
				GenerateRandomSpawningLocation(Location);
				Location = Location + SpawnOffset;

				FRotator rotation = FRotator(0, 0, FMath::RandRange(0, 1000) / 1000.0);
				AActor* NewSpawn = World->SpawnActor<AActor>(ClassToSpawn, Location, rotation, spawnParams);
				
				bActorIsOnSpawner = true;
				Spawns.Add(NewSpawn);
			}
		} 
	}
	
	return Spawns;
}

void ASpawner::AddSpawnVolume(AActor* NewVolume) 
{
	SpawnVolumes.Add(NewVolume);
}