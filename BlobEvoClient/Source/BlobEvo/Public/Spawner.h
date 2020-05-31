// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Spawner.generated.h"

UCLASS()
class BLOBEVO_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	TArray<AActor*> SpawnByCount(int32 Count, TSubclassOf<AActor> ClassToSpawn);  
	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	AActor* SpawnByLocation(FVector SpawnLocation, TSubclassOf<AActor> ClassToSpawn);  

	void GenerateRandomSpawningLocation(FVector& OutLocation);
	void AddSpawnVolume(AActor* NewVolume);

private:
	UPROPERTY(EditAnywhere, Category=Spawning)
	int32 SpawnSpacing = 100;

	UPROPERTY(EditAnywhere, Category=Spawning)
	FVector SpawnOffset;

	UPROPERTY()
	TArray<AActor*> Spawns;

	UPROPERTY()
	TArray<AActor*> SpawnVolumes;
};
