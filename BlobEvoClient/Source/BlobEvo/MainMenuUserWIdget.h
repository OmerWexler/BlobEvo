// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWIdget.generated.h"

/**
 * 
 */
UCLASS()
class BLOBEVO_API UMainMenuUserWIdget : public UUserWidget
{
	GENERATED_BODY()

public:
	void StartPythonServer();
};
