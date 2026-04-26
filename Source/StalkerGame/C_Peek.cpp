// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Peek.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyCharacter.h"

void UC_Peek::AdjustCameraOffset()
{
}

void UC_Peek::LerpForward()
{
}

void UC_Peek::LerpReverse()
{
}

void UC_Peek::AdjustLerpAmount(float amount)
{
}

void UC_Peek::HandlePeek_Implementation(bool canPeek)
{

	//--First Trace--//

	FVector AdjustedForwardVector = FVector(UCamera->GetForwardVector().X, AOwner->GetActorForwardVector().Y, 0);

	FVector startPos = UCamera->GetComponentLocation();
	FVector endPos = startPos + (AdjustedForwardVector * _maxCanPeekDistance);

	FCollisionShape trace = FCollisionShape::MakeSphere(_firstRayCheckRadius);

	FHitResult hitResult;
	FCollisionQueryParams queryParam;
	queryParam.AddIgnoredActor(AOwner);

	FName fProfileName = TEXT("BlockAll");

	bool hit = GetWorld()->SweepSingleByProfile(
		hitResult,
		startPos,
		endPos,
		FQuat::Identity,
		fProfileName,
		trace,
		queryParam
	);
	
	UE_LOG(LogTemp, Warning, TEXT("HANDLE PEEK"));

	if (!hit) 
	{
		_currentEyeHeight = 0;
		_currentEyeLocation = FVector();
		return;
	}

	_currentEyeHeight = hitResult.ImpactPoint.Z;
	_currentEyeLocation = hitResult.ImpactPoint;

	//--Second Trace--//
	startPos = FVector(startPos.X, startPos.Y, startPos.Z + _MaxPeekHeight);

	endPos = (AdjustedForwardVector * _maxCanPeekDistance);
	endPos.Normalize();//Check if neccessary
	endPos *= _MaxDistanceOverhead;

	trace = FCollisionShape::MakeSphere(_firstRayCheckRadius);


	hit = GetWorld()->SweepSingleByProfile(
		hitResult,
		startPos,
		endPos + startPos,
		FQuat::Identity,
		fProfileName,
		trace,
		queryParam
	);

	if (hit)
		return;

	//--Third Trace--//
	startPos = FVector(_currentEyeLocation.X, _currentEyeLocation.Y, _currentEyeLocation.Z + _MaxPeekHeight);
	endPos = _currentEyeLocation - startPos;

	trace = FCollisionShape::MakeSphere(_firstRayCheckRadius);

	hit = GetWorld()->SweepSingleByProfile(
		hitResult,
		startPos,
		endPos + startPos,
		FQuat::Identity,
		fProfileName,
		trace,
		queryParam
	);

	if (!hit)
		return;

	FVector camToPointVec = hitResult.ImpactPoint - UCamera->GetComponentLocation();

	FTransform transform = UCamera->GetComponentTransform();
	FTransform t = FTransform(
		{0.0f, transform.Rotator().Yaw, 0.0f},
		FVector::ZeroVector,
		transform.GetScale3D()
	);

	FMatrix m = t.ToMatrixWithScale();
	_currentCameraOffsetVector = m.InverseTransformVector(hitResult.Location - UCamera->GetComponentLocation());

	/*AOwner->bCanMove = false;
	SetPlayerPeek(true);*/

	DrawDebugLine(
		GetWorld(),
		UCamera->GetComponentLocation(),
		_currentCameraOffsetVector + UCamera->GetComponentLocation(),
		FColor::Green,
		true,
		2.0f,
		0,
		2.0f
	);

	LerpForward();
}

void UC_Peek::SetPlayerPeek_Implementation(bool isPeeking)
{
	_isPeeking = isPeeking;
}



