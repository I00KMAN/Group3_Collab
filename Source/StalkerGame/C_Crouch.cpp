// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Crouch.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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

}

void UC_Crouch::ReverseLerpForwardTimer()
{
}

void UC_Crouch::AdjustLerpAmount(float Amount)
{
}

void UC_Crouch::TryUnCrouch()
{
}
