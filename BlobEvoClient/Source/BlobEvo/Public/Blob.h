// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Blob.generated.h"

UCLASS()
class BLOBEVO_API ABlob : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABlob();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool ShouldLive(); 

	UFUNCTION(BlueprintCallable)
	int32 GetNumberOfNewBlobs(); 

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToNextRedirection = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinRedirectionInterval = 2.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DonutsToReproduce = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DonutsToLive = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRedirectionInterval = 4.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInRound = false;

	UPROPERTY(BlueprintReadWrite)
	bool bHitSpawner = false;

	UPROPERTY(BlueprintReadWrite)
	int32 DonutsEaten = 0;

	UPROPERTY(BlueprintReadWrite)
	FVector InitialLocation;

	UFUNCTION(BlueprintCallable)
	void EatDonut(AActor* Donut);

	UFUNCTION(BlueprintCallable)
	void RandomizeTimeToRedirection();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
