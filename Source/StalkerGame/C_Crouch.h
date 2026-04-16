// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Crouch.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AMyCharacter;

struct FRichCurve;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable )
class STALKERGAME_API UC_Crouch : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_Crouch();

protected:
	virtual void BeginPlay() override;
	
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch|Components")
	TObjectPtr<AMyCharacter> AOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crouch|Components")
	TObjectPtr<UCameraComponent> UCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch|Components")
	TObjectPtr<USpringArmComponent> USpringArm;

	//Lerp Functions
	UFUNCTION(BlueprintCallable)
	void LerpForwardTimer();
	UFUNCTION(BlueprintCallable)
	void ReverseLerpForwardTimer();
	UFUNCTION()
	void Lerp(float Amount);
	UFUNCTION()
	void OffsetCamera();

	//Check if Uncrouch is possible
	UFUNCTION(BlueprintCallable)
	void TryUnCrouch();

	//Lerp Timer Handles
	UPROPERTY(BlueprintReadWrite, Category="Crouch")
	FTimerHandle FLerpHandle;
	UPROPERTY(BlueprintReadWrite, Category = "Crouch")
	FTimerHandle FReverseLerpHandle;
	UPROPERTY(BlueprintReadWrite, Category = "Crouch")
	FTimerHandle FUnCrouchCheckTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crouch")
	FRuntimeFloatCurve FLerpCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Crouch")
	float CrouchHeightOffset;

private:

	//Lerp Variables
	float CurrentOffset = 0.0f;
	float LerpAmount;
};
