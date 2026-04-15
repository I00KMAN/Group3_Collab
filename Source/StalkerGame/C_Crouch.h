// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Crouch.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
	TSubclassOf<ACharacter> _Owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Crouch|Components")
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch|Components")
	TObjectPtr<USpringArmComponent> _SpringArm;	

	//Lerp Functions
	UFUNCTION(BlueprintCallable)
	void LerpForwardTimer();
	UFUNCTION(BlueprintCallable)
	void ReverseLerpForwardTimer();
	UFUNCTION(BlueprintCallable)
	void AdjustLerpAmount(float Amount);

	//Check if Uncrouch is possible
	UFUNCTION(BlueprintCallable)
	void TryUnCrouch();

	//Lerp Timer Handles
	UPROPERTY(BlueprintReadWrite, Category="Crouch")
	FTimerHandle LerpHandle;
	UPROPERTY(BlueprintReadWrite, Category = "Crouch")
	FTimerHandle ReverseLerpHandle;

private:

	//Lerp Variables
	float CurrentOffset;
	float LerpAmount;
};
