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
	UFUNCTION()
	void LerpForward();
	UFUNCTION()
	void LerpReverse();
	UFUNCTION()
	void AdjustLerpAmount(float amount);

	//Peek Logic
	UFUNCTION()
	void HandlePeek(bool canPeek);

protected:
	//virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void SetPlayerPeek(bool isPeeking);

	virtual void SetPlayerPeek_Implementation(bool isPeeking);

private:

//Variables
public:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Peek|Components")
	TObjectPtr<AMyCharacter> AOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Peek|Components")
	TObjectPtr<UCameraComponent> UCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Peek|Components")
	TObjectPtr<USpringArmComponent> USpringArm;

	float _lerpAmount;
	bool _isPeeking;
private:
};
