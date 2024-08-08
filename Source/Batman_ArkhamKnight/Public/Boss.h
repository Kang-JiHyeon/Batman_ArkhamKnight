// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

UCLASS()
class BATMAN_ARKHAMKNIGHT_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:
	UPROPERTY(EditAnywhere,Category = FSMComponent)
	class UBossFSM* fsm;

	UPROPERTY(EditAnywhere)
	class ABoss* me;
	
	// boss tail
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* TailComp;
	float time = 0.0f;
};
