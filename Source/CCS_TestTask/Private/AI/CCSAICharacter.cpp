// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CCSAICharacter.h"

#include "Core/CCSGameStateBase.h"


ACCSAICharacter::ACCSAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACCSAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ACCSGameStateBase* CCSGameState = Cast<ACCSGameStateBase>(GetWorld()->GetGameState()))
	{
		CCSGameState->RegisterNewParticipant(this);
	}
}

void ACCSAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCSAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCSAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

