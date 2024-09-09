// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CCSAICharacter.h"

#include "Core/CCSGameStateBase.h"
#include "Net/UnrealNetwork.h"


ACCSAICharacter::ACCSAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACCSAICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACCSAICharacter, TargetToy);
}

void ACCSAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		if (ACCSGameStateBase* CCSGameState = Cast<ACCSGameStateBase>(GetWorld()->GetGameState()))
		{
			CCSGameState->RegisterNewParticipant(this);

			CCSGameState->OnToyLaunchedDelegate.AddDynamic(this, &ACCSAICharacter::OnToyLaunched);
			CCSGameState->OnToyCapturedDelegate.AddDynamic(this, &ACCSAICharacter::OnToyCaptured);
		}
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

void ACCSAICharacter::OnToyLaunched(AToy* InToy)
{
	TargetToy = InToy;
}

void ACCSAICharacter::OnToyCaptured(AActor* InActor)
{
	TargetToy = nullptr;
}

