// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "PlayerPawn.h"
#include "GameManager.generated.h"

UCLASS()
class BLOBEVO_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenRounds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RoundLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> AllDonuts;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfDonuts;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
