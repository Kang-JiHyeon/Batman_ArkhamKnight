// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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

UENUM()
enum class EEnemyDirection
{
	Front,
	Back,
	Left,
	Right
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
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_Attack;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* IA_BossAttack;

	// 애니메이션
	UPROPERTY(EditDefaultsOnly)
	class UPlayerAnim* PlayerAnim;
	// 애니메이션 몽타주
	UPROPERTY(EditAnywhere)
	class UAnimMontage* FrontAttackMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* BackAttackMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* DamageMontage;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* BossAttackMontage;

	// 보스
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class ABoss* TargetBoss;
	
	// 죄수
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> PrisonerFactory;

	UPROPERTY(VisibleDefaultsOnly)
	class APrisoner* TargetPrisoner;
	UPROPERTY()
	class APrisoner* OverlapPrisoner;

	// 방향
	FVector Direction;

	// 움직임 여부
	bool bMoveInputPressed;
	bool bMovingToTarget;
	bool bRotatingToTarget;

	// 공격 
	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 1000;
	int32 AttackMaxSpeed = 3000;
	int32 DefaultMaxSpeed;
	int32 AnimComboCount = 0;

	// 보스 공격
	UPROPERTY(EditDefaultsOnly)
	int32 MaxBossAttackComboCount = 12;
	int32 AttackComboCount = 0;
	

	// 회피
	UPROPERTY(EditDefaultsOnly)
	float DodgeSpeed = 700;
	UPROPERTY(EditDefaultsOnly)
	float DoublePressInterval = 0.5f;
    float LastDodgeInputPressTime = 0;
    bool bDodgeInputPressed = false;

	// 피격
	UPROPERTY(EditDefaultsOnly)
	int32 MaxHP = 20;
	int32 HP;

	UPROPERTY(EditDefaultsOnly)
	float DamageIdleTime = 1.5f;
	bool bDamageState;

	// TimerHandler
	FTimerHandle DamageTimerHandler;

	// Level Sequence
	//UPROPERTY(EditDefaultsOnly)
	//class UPlayerBossAttackSequence* LevelSequenceComp;

	class APlayerGameModeBase* MyGameModeBase;

	// Motion Warping
	UPROPERTY(EditDefaultsOnly)
	class UMotionWarpingComponent* MotionWarpingComp;

private:
	// Input
	void OnActionMove(const FInputActionValue& Value);
	void OnActionMoveCompleted(const FInputActionValue& Value);
	void OnActionLook(const FInputActionValue& Value);
	void OnActionDodge(const FInputActionValue& Value);
	void OnActionAttack(const FInputActionValue& Value);
	void OnActionBossAttack(const FInputActionValue& Value);

	// Move
	void MoveToTarget(AActor* Target);
	void RotateToTarget(AActor* Target);
	bool IsLockedMove() const;
	EEnemyDirection GetTargetVerticalDirection(AActor* TargetActor);
	EEnemyDirection GetTargetHorizontalDirection(AActor* TargetActor);

	// Animation
	void PlayAttackAnimation();
	void PlayBossAttack();

	void SetGlobalTimeDilation(float Value);
	void SetAttackComboCount(float Value);

	void CallDelegateLevelSequnce();
public:
	bool bIsSlow;

	void ResetCombo();
	void OnTakeDamage(AActor* OtherActor, int32 Damage);
	void OnEndDamage();
	void SetMeshCollisionEnabled(bool bValue);

	UFUNCTION(BlueprintCallable)
	void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
