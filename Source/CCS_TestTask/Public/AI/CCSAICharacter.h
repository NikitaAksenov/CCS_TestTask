// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "CCSAICharacter.generated.h"


UCLASS()
class CCS_TESTTASK_API ACCSAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACCSAICharacter();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
