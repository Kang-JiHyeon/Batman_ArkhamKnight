// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "PlayerCharacter.generated.h"

UENUM()
enum class EPlayerState
{
	Idle, 
	Move,
	Attack,
	Dodge,
	Damage,
	Die
};



UCLASS()
class BATMAN_ARKHAMKNIGHT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// 카메라
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComp;

	// 키 입력
	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* IMP_Player;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Dodge;

	// 애니메이션
	UPROPERTY(EditDefaultsOnly)
	class UPlayerAnim* PlayerAnim;

	// 방향
	FVector Direction;

	EPlayerState PlayerState = EPlayerState::Idle;

	// 움직임 여부
	bool bMove;

	// 점프 관련 변수
	bool bIsDodgeKeyPressed = false;
	float LastDodgeKeyPressTime = 0;
	float DoublePressInterval = 0.5f;

private:
	void OnActionMove(const FInputActionValue& Value);
	void OnActionMoveCompleted(const FInputActionValue& Value);
	void OnActionLook(const FInputActionValue& Value);
	void OnActionDodge(const FInputActionValue& Value);
	void OnActionDodgeCompleted(const FInputActionValue& Value);
};
