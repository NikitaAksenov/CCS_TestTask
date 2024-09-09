// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "ToyComponent.generated.h"


class ACCSGameStateBase;
class AToy;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CCS_TESTTASK_API UToyComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UToyComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Toy")
	TArray<TSubclassOf<AToy>> AvailableToyClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Toy")
	TObjectPtr<AToy> CurrentToy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Toy")
	float LaunchModifier = 50000.f;


	TWeakObjectPtr<ACCSGameStateBase> GameState;


protected:
	UFUNCTION()
	void OnToyCaptured(AActor* InActor);

	UFUNCTION(Server, Reliable)
	void SetNewToy(TSubclassOf<AToy> InToyClass);


public:
	UFUNCTION(Server, Reliable)
	void SelectNextToy();

private:
	int CurrentToyClassIndex;

public:
	UFUNCTION(Server, Reliable)
	void LaunchToy();
};
