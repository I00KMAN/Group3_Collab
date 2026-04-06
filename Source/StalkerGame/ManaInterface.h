// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ManaInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UManaInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STALKERGAME_API IManaInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IMana")
	void C_AddMana(float Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IMana")
	void C_SubMana(float Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IMana")
	float C_GetCurrentMana();
};
