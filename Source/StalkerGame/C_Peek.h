// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Peek.generated.h"

class AMyCharacter;
class UCameraComponent;
class USpringArmComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class STALKERGAME_API UC_Peek : public UActorComponent
{
	GENERATED_BODY()

//Functions
public:	
	//UC_Peek();

	UFUNCTION()
	void AdjustCameraOffset();

	//Lerp Logic
	UFUNCTION(BlueprintCallable)
	void LerpForward();
	UFUNCTION(BlueprintCallable)
	void LerpReverse();
	UFUNCTION()
	void AdjustLerpAmount(float amount);

	

protected:
	//virtual void BeginPlay() override;

	//Peek Logic
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandlePeek(bool canPeek);
	virtual void HandlePeek_Implementation(bool canPeek);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPlayerPeek(bool isPeeking);
	virtual void SetPlayerPeek_Implementation(bool isPeeking);

//Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Peek")
	float _maxCanPeekDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Peek")
	float _MaxPeekHeight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Peek")
	float _MaxDistanceOverhead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Peek")
	float _firstRayCheckRadius;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Peek|Components")
	TObjectPtr<AMyCharacter> AOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Peek|Components")
	TObjectPtr<UCameraComponent> UCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Peek|Components")
	TObjectPtr<USpringArmComponent> USpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Peek")
	FRuntimeFloatCurve _LerpCurve;
	UPROPERTY(BlueprintReadWrite, Category = "Peek")
	bool _isPeeking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Peek")
	FVector _cameraPeekOffset;

	FTimerHandle _lerpForwardTimer;
	FTimerHandle _lerpReverseTimer;

	float _lerpAmount;
	float _currentEyeHeight;
	FVector _currentEyeLocation;
	FVector _currentCameraOffsetVector;
	FVector _previousOffsetVector;

	
private:
};
