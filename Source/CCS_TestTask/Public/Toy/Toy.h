// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Toy.generated.h"


class USphereComponent;

UCLASS()
class CCS_TESTTASK_API AToy : public AActor
{
	GENERATED_BODY()
	
public:	
	AToy();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* PickUpSphere;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Toy")
	float Score;

protected:
	UFUNCTION()
	void OnToyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UFUNCTION(BlueprintCallable)
	float GetScore() const;

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetStaticMesh() const;
};
