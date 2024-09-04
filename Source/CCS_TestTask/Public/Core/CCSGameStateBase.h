// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "CCSGameStateBase.generated.h"


USTRUCT(BlueprintType)
struct FParticipantScoreInfo
{
	GENERATED_BODY()

	FParticipantScoreInfo()
	{
		Participant = nullptr;
		Score = 0.f;
	}

	FParticipantScoreInfo(AActor* InParticipant)
	{
		Participant = InParticipant;
		Score = 0.f;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AActor* Participant;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Score;

	bool operator==(const FParticipantScoreInfo& Other) const
	{
		return Participant == Other.Participant;
	}
};


/**
 * 
 */
UCLASS()
class CCS_TESTTASK_API ACCSGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:
	ACCSGameStateBase();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	TArray<FParticipantScoreInfo> ParticipantScoreInfos;


public:
	void RegisterNewParticipant(AActor* InParticipant);

	void IncreaseParticipantScore(AActor* InParticipant, float InDeltaScore);
};
