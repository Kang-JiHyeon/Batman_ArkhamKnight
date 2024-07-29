// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UENUM(BlueprintType)
enum class EComboAttackState : uint8
{
	Punching_Right,
	Punching_Left,
	Hook_Right
};

UCLASS()
class BATMAN_ARKHAMKNIGHT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Speed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bDodge = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAttack = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EComboAttackState ComboAttackState;

public:
	void SetDodge(bool bValue);
	void SetAttack(bool bValue);

	UFUNCTION(BlueprintCallable)
	void OnEndAttackPunchingRight();
};
