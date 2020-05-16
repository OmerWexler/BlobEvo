// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOBEVO_API USpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SpawnBlobCount(int32 BlobCount);
	void GenerateRandomSpawningLocation(FVector& OutLocation);

private:
	UPROPERTY(EditAnywhere, Category=Spawning)
	int32 InitialNumberOfBlobs = 0;
	
	UPROPERTY(EditAnywhere, Category=Spawning)
	int32 SpawnSpacing = 100;

	UPROPERTY(EditAnywhere, Category=Spawning)
	TSubclassOf<AActor> BlobClass;
	
	UPROPERTY(EditAnywhere, Category=Spawning)
	TArray<AActor*> SpawnBoundries;
	
	UPROPERTY()
	TArray<AActor*> Blobs;
};
