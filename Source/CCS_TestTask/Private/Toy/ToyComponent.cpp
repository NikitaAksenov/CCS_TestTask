// Fill out your copyright notice in the Description page of Project Settings.


#include "Toy/ToyComponent.h"

#include "Core/CCSGameStateBase.h"
#include "Toy/Toy.h"


UToyComponent::UToyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UToyComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(!AvailableToyClasses.IsEmpty(), TEXT("%s has no ToyClasses assigned"), *GetName());
	
	GameState = Cast<ACCSGameStateBase>(GetWorld()->GetGameState());
	check(GameState != nullptr);

	GameState->OnToyCapturedDelegate.AddDynamic(this, &UToyComponent::OnToyCaptured);

	CurrentToyClassIndex = 0;
	SetNewToy(AvailableToyClasses[CurrentToyClassIndex]);
}

void UToyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UToyComponent::OnToyCaptured(AActor* InActor)
{
	SetNewToy(AvailableToyClasses[CurrentToyClassIndex]);
}

void UToyComponent::SetNewToy_Implementation(TSubclassOf<AToy> InToyClass)
{
	if (!GameState->CanSpawnToy())
	{
		return;
	}
	
	if (CurrentToy)
	{
		CurrentToy->Destroy();
	}

	if (AToy* NewToy = GetWorld()->SpawnActor<AToy>(InToyClass, GetComponentLocation(), GetComponentRotation()))
	{
		CurrentToy = NewToy;
		CurrentToy->GetStaticMesh()->SetSimulatePhysics(false);
		CurrentToy->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	}
}

void UToyComponent::SelectNextToy_Implementation()
{
	if (!GameState->CanSpawnToy())
	{
		return;
	}
	
	CurrentToyClassIndex++;
	if (!AvailableToyClasses.IsValidIndex(CurrentToyClassIndex))
	{
		CurrentToyClassIndex = 0;
	}

	SetNewToy(AvailableToyClasses[CurrentToyClassIndex]);
}

void UToyComponent::LaunchToy_Implementation()
{
	if (!CurrentToy)
	{
		return;
	}

	CurrentToy->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	CurrentToy->GetStaticMesh()->SetSimulatePhysics(true);
	CurrentToy->GetStaticMesh()->SetEnableGravity(true);

	const FVector LaunchVector = GetForwardVector() + FVector(0.f, 0.f, 1.f);
	CurrentToy->GetStaticMesh()->AddImpulse(LaunchVector * LaunchModifier);

	if (ACCSGameStateBase* CCSGameState = Cast<ACCSGameStateBase>(GetWorld()->GetGameState()))
	{
		CCSGameState->OnToyLaunched(CurrentToy);
	}
}

