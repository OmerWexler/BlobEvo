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

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float EndurenceInSEC = 50;

	UPROPERTY(EditAnywhere)
	float SpeedInMPS = 5;
	
	UPROPERTY(EditAnywhere)
	float SizeInPrecent = 100;
	
	UPROPERTY(EditAnywhere)
	float RadarInM = 0;
	
	UPROPERTY()
	bool bIsCannibal = false;

	UPROPERTY()
	FVector InitialTranslation;
	
	UPROPERTY()
	int32 FoodEaten = 0;

	void AddAndApplyModifiers(float EndurenceBonus, float SpeedBonus, float SizeBonus, float RadarInM);
	void ActivateCannibal();
	void BeginRound();
	void EndRound();
	void Duplicate();
	void ResetToSpawner();
	bool IsOverlappingFood();
	bool EatOverlappedFood();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
