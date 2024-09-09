// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CCSGameStateBase.h"

#include "Core/CCSGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Toy/Toy.h"

ACCSGameStateBase::ACCSGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ACCSGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACCSGameStateBase, ParticipantScoreInfos);
	DOREPLIFETIME(ACCSGameStateBase, CurrentToy);
	DOREPLIFETIME(ACCSGameStateBase, bCurrentToyLaunched);
	DOREPLIFETIME(ACCSGameStateBase, TimeLeft);
	DOREPLIFETIME(ACCSGameStateBase, OnToyCapturedDelegate);
}

void ACCSGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		ACCSGameModeBase* GameMode = Cast<ACCSGameModeBase>(UGameplayStatics::GetGameMode(this));
		TimeLeft = GameMode->GetGameDuration();
	}
}

void ACCSGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		TimeLeft -= DeltaSeconds;
	}

	int Index = 1;
	for (const auto& ParticipantScoreInfo : ParticipantScoreInfos)
	{
		const FString DebugMessage = FString::Printf(TEXT("#%02d %s %.2f"), Index, *ParticipantScoreInfo.Participant->GetName(), ParticipantScoreInfo.Score);
		GEngine->AddOnScreenDebugMessage(Index, 0.f, FColor::Orange, DebugMessage);
		Index++;
	}

	{
		const FString DebugMessage = FString::Printf(TEXT("Toy is %s"), bCurrentToyLaunched ? TEXT("in game") : TEXT("not in game"));
		GEngine->AddOnScreenDebugMessage(Index, 0.f, FColor::Orange, DebugMessage);
	}
}

void ACCSGameStateBase::OnRep_ParticipantScoreInfos()
{
	OnParticipantsUpdatedDelegate.Broadcast();
}

void ACCSGameStateBase::RegisterNewParticipant(AActor* InParticipant)
{
	if (!InParticipant)
	{
		return;
	}

	ParticipantScoreInfos.AddUnique(FParticipantScoreInfo(InParticipant));

	OnNewParticipantRegisteredDelegate.Broadcast(InParticipant);
}

void ACCSGameStateBase::IncreaseParticipantScore(AActor* InParticipant, float InDeltaScore)
{
	if (!InParticipant)
	{
		return;
	}

	const int ParticipantScoreInfoIndex = ParticipantScoreInfos.Find(InParticipant);
	if (ParticipantScoreInfoIndex != INDEX_NONE)
	{
		ParticipantScoreInfos[ParticipantScoreInfoIndex].Score += InDeltaScore;
	}
}

void ACCSGameStateBase::RegisterNewToy(AToy* InToy)
{
	CurrentToy = InToy;

	OnToySpawnedDelegate.Broadcast(CurrentToy);
}

void ACCSGameStateBase::OnToyLaunched(AToy* InToy)
{
	bCurrentToyLaunched = true;
	OnToyLaunchedDelegate.Broadcast(InToy);
}

void ACCSGameStateBase::OnGameFinished_Implementation()
{
	OnGameFinishedDelegate.Broadcast();
}

void ACCSGameStateBase::OnToyCaptured(AToy* InToy, AActor* InActor)
{
	IncreaseParticipantScore(InActor, InToy->GetScore());
	
	CurrentToy = nullptr;
	bCurrentToyLaunched = false;

	OnToyCaptured_NetMulticast(InToy, InActor);
}

void ACCSGameStateBase::OnToyCaptured_NetMulticast_Implementation(AToy* InToy, AActor* InActor)
{
	OnToyCapturedDelegate.Broadcast(InActor);
}

bool ACCSGameStateBase::CanSpawnToy() const
{
	return !bGameFinished && !bCurrentToyLaunched;
}

AToy* ACCSGameStateBase::GetCurrentToy() const
{
	return CurrentToy;
}
