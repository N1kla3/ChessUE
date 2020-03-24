// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"

// Sets default values
AGamePawn::AGamePawn(const FObjectInitializer& Initialize)
{
	Super(Initialize);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AGamePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGamePawn::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	
}


// Called every frame
void AGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

