// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Engine/World.h"

// Sets default values for this component's properties
Spawner::UWorldBlobManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Spawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnInitialBlobCount();
}

void Spawner::SpawnInitialBlobCount() {
	
	if (BlobClass) {
		UWorld* world = GetWorld();

		if (world) {
			for (int32 i = 0; i < InitialNumberOfBlobs; i++) {
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = GetOwner();

				const FVector location = FVector(0, 0, 100);
				const FRotator rotation = FRotator(0, 0, 0);

				AActor* blob = world->SpawnActor<AActor>(BlobClass, location, rotation, spawnParams);
			}
		} 
	}
}

// Called every frame
void Spawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

