// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CCSGameStateBase.h"

#include "Net/UnrealNetwork.h"

ACCSGameStateBase::ACCSGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ACCSGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACCSGameStateBase, ParticipantScoreInfos);
}

void ACCSGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	int Index = 1;
	for (const auto& ParticipantScoreInfo : ParticipantScoreInfos)
	{
		const FString DebugMessage = FString::Printf(TEXT("#%02d %s %.2f"), Index, *ParticipantScoreInfo.Participant->GetName(), ParticipantScoreInfo.Score);
		GEngine->AddOnScreenDebugMessage(Index, 0.f, FColor::Orange, DebugMessage);
		Index++;
	}
}

void ACCSGameStateBase::RegisterNewParticipant(AActor* InParticipant)
{
	if (!InParticipant)
	{
		return;
	}

	ParticipantScoreInfos.AddUnique(FParticipantScoreInfo(InParticipant));
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
