// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "CCSGameStateBase.generated.h"


class AToy;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameFinished);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewParticipantRegistered, AActor*, Actor);


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnParticipantsUpdated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToySpawned, AToy*, Toy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToyLaunched, AToy*, Toy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToyCaptured, AActor*, Actor);


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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_ParticipantScoreInfos)
	TArray<FParticipantScoreInfo> ParticipantScoreInfos;

	UFUNCTION()
	void OnRep_ParticipantScoreInfos();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	AToy* CurrentToy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
	bool bCurrentToyLaunched;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	float TimeLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool bGameFinished;

public:
	void RegisterNewParticipant(AActor* InParticipant);

	void IncreaseParticipantScore(AActor* InParticipant, float InDeltaScore);

	void RegisterNewToy(AToy* InToy);

	void OnToyLaunched(AToy* InToy);

	void OnToyCaptured(AToy* InToy, AActor* InActor);

	UFUNCTION(NetMulticast, Reliable)
	void OnToyCaptured_NetMulticast(AToy* InToy, AActor* InActor);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void OnGameFinished();

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameFinished OnGameFinishedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnNewParticipantRegistered OnNewParticipantRegisteredDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnParticipantsUpdated OnParticipantsUpdatedDelegate;
	
	FOnToySpawned OnToySpawnedDelegate;
	
	FOnToySpawned OnToyLaunchedDelegate;

	UPROPERTY(BlueprintAssignable, Replicated)
	FOnToyCaptured OnToyCapturedDelegate;

public:
	UFUNCTION(BlueprintCallable)
	bool CanSpawnToy() const;

	UFUNCTION(BlueprintCallable)
	AToy* GetCurrentToy() const;
};
