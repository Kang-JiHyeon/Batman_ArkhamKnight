﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMotionWarpingComponent.h"
#include "PlayerCharacter.h"
#include "Boss.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../../../Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingComponent.h"


// Sets default values for this component's properties
UPlayerMotionWarpingComponent::UPlayerMotionWarpingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerMotionWarpingComponent::BeginPlay()
{
	Super::BeginPlay();

	Me = Cast<APlayerCharacter>(GetOwner());

}

// Called every frame
void UPlayerMotionWarpingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPlayerMotionWarpingComponent::OnInitialize(AActor* OtherActor)
{
	if(OtherActor == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("UPlayerMotionWarpingComponent : OnInitialize 실행"));

	TargetActor = OtherActor;

	TArray<UActorComponent*> components = TargetActor->K2_GetComponentsByClass(UPlayerAttackPointComponent::StaticClass());

	if (components.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayerMotionWarpingComponent : Target에 UPlayerAttackPointComponent 컴포넌트가 없습니다. "));
		return;
	}

	for (auto component : components)
	{
		auto* attackPointComp = Cast<UPlayerAttackPointComponent>(component);

		if (attackPointComp != nullptr)
		{
			AttackPoints.Add(attackPointComp->AttackType, attackPointComp);
		}
	}
}

void UPlayerMotionWarpingComponent::AddAndUpdateMotionWarping(EAttackType AttackType)
{
	if(AttackPoints.Contains(AttackType) == false) return;

	auto* attackPoint = AttackPoints[AttackType];

	// 이동할 위치 설정
	FVector targetLoc = attackPoint->GetComponentLocation();
	// 회전 설정
	FVector targetDir = UKismetMathLibrary::GetDirectionUnitVector(Me->GetActorLocation(), targetLoc);
	FRotator targetRot = UKismetMathLibrary::MakeRotFromX(targetDir);

	// 모션 워핑 실행
	Me->MotionWarpingComp->AddOrUpdateWarpTargetFromLocationAndRotation(GetEnumValue(AttackType), targetLoc, targetRot);
}

FName UPlayerMotionWarpingComponent::GetEnumValue(EAttackType AttackType)
{
	const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAttackType"), true);

	FString EnumToString = TEXT("Invalid");
	if (CharStateEnum)
	{
		EnumToString = CharStateEnum->GetNameStringByValue((int64)AttackType);
		UE_LOG(LogTemp, Warning, TEXT("AddMotionWarping : %s"), *EnumToString);

	}
	
	return FName(EnumToString);
}

