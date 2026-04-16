// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Crouch.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyCharacter.h"
#include "TimerManager.h"
#include "Curves/RichCurve.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UC_Crouch::UC_Crouch()
{
}


// Called when the game starts
void UC_Crouch::BeginPlay()
{
	Super::BeginPlay();
	
}

void UC_Crouch::LerpForwardTimer()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	TimerManager.ClearTimer(FUnCrouchCheckTimerHandle);

	FTimerDelegate timerDelegate;

	TimerManager.ClearTimer(FReverseLerpHandle);

	timerDelegate.BindUObject(this, &UC_Crouch::Lerp, GetWorld()->GetDeltaSeconds());
	TimerManager.SetTimer(FLerpHandle, timerDelegate, GetWorld()->GetDeltaSeconds(), true);
	AOwner->Crouch();
}

void UC_Crouch::ReverseLerpForwardTimer()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	FTimerDelegate timerDelegate;

	TimerManager.ClearTimer(FLerpHandle);

	timerDelegate.BindUObject(this, &UC_Crouch::Lerp, GetWorld()->GetDeltaSeconds() * -1.0f);
	TimerManager.SetTimer(FReverseLerpHandle, timerDelegate, GetWorld()->GetDeltaSeconds(), true);
}

void UC_Crouch::Lerp(float Amount)
{
	float Max = 0.f;
	float Min = 0.f;

	FLerpCurve.GetRichCurveConst()->GetTimeRange(Min, Max);

	LerpAmount = FMath::Clamp(LerpAmount + Amount, Min, Max);

	if(Min == LerpAmount)
	{
		GetWorld()->GetTimerManager().ClearTimer(FReverseLerpHandle);
	}
	else if (Max == LerpAmount) 
	{
		GetWorld()->GetTimerManager().ClearTimer(FLerpHandle);
	}

	OffsetCamera();
}

void UC_Crouch::OffsetCamera()
{

	float offsetAmount = 0.f;

	offsetAmount = FMath::Lerp(0.f, CrouchHeightOffset * -1.0f, FLerpCurve.GetRichCurveConst()->Eval(LerpAmount));
	USpringArm->AddLocalOffset({0.0f, 0.0f, offsetAmount - CurrentOffset });

	CurrentOffset = offsetAmount;
}

void UC_Crouch::TryUnCrouch()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	FTimerDelegate timerDelegate;

	timerDelegate.BindUObject(this, &UC_Crouch::CheckCanUnCrouch);
	TimerManager.SetTimer(FUnCrouchCheckTimerHandle, timerDelegate, GetWorld()->GetDeltaSeconds(), true);
}

void UC_Crouch::CheckCanUnCrouch()
{
	UWorld* world = GetWorld();

	if (!world) return;

	FTimerManager& TimerManager = world->GetTimerManager();

	FVector fStartPos = AOwner->GetActorLocation();
	FVector fEndPos = fStartPos + (AOwner->GetActorUpVector() * UnCrouchOverheadCheckHeight);

	float Radius = 0.0f;
	float HalfHeight = 0.0f;

	AOwner->GetCapsuleSize(Radius, HalfHeight);
	FCollisionShape fCapsuleTrace = FCollisionShape::MakeCapsule(Radius, HalfHeight);

	FHitResult fHitResult;
	FCollisionQueryParams fQueryParams;
	fQueryParams.AddIgnoredActor(AOwner);

	FName fProfileName = TEXT("BlockAll");

	bool bHit = world->SweepSingleByProfile(
		fHitResult,
		fStartPos,
		fEndPos,
		FQuat::Identity,
		fProfileName,
		fCapsuleTrace,
		fQueryParams
	);

	if (!bHit) 
	{
		if (AOwner->bIsPeeking)
		{
			AOwner->CancelPeek();
		}

		TimerManager.ClearTimer(FUnCrouchCheckTimerHandle);
		ReverseLerpForwardTimer();
		AOwner->UnCrouch();
	}
}