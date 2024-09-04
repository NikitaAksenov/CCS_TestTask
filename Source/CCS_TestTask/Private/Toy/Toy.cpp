// Fill out your copyright notice in the Description page of Project Settings.


#include "Toy/Toy.h"

#include "AI/CCSAICharacter.h"
#include "Components/SphereComponent.h"
#include "Core/CCSGameStateBase.h"


AToy::AToy()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	PickUpSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpSphere"));
	PickUpSphere->SetupAttachment(StaticMesh);
}

void AToy::BeginPlay()
{
	Super::BeginPlay();

	PickUpSphere->OnComponentBeginOverlap.AddDynamic(this, &AToy::OnToyBeginOverlap);
}

void AToy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToy::OnToyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		ACCSAICharacter* AICharacter = Cast<ACCSAICharacter>(OtherActor);
		ACCSGameStateBase* CCSGameState = Cast<ACCSGameStateBase>(GetWorld()->GetGameState());
		
		if (AICharacter &&
			CCSGameState)
		{
			CCSGameState->IncreaseParticipantScore(OtherActor, Score);

			Destroy();
			
		}
	}
}

