// Fill out your copyright notice in the Description page of Project Settings.


#include "Blob.h"
#include "GameFramework/Actor.h"

// Sets default values
ABlob::ABlob()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlob::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlob::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABlob::EatDonut(AActor* Donut) {
	Donut->Destroy();
	DonutsEaten++;
}

bool ABlob::ShouldLive() {
	return DonutsEaten >= DonutsToLive;
}

int32 ABlob::GetNumberOfNewBlobs() {
	if (DonutsEaten >= DonutsToReproduce) {
		return DonutsEaten - DonutsToReproduce + 1;
	} else {
		return 0;
	}
}
