// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOBEVO_API UWorldBlobManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorldBlobManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RegisterBlob();
	void SpawnInitialBlobCount();

private:
	UPROPERTY()
	int32 CurrentNumberOfBlobs = 0;
	
	UPROPERTY(EditAnywhere)
	int32 InitialNumberOfBlobs = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BlobClass;
};
