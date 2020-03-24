// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AGamePawn::AGamePawn(const FObjectInitializer& GamePawnInitialize) :
	Super(GamePawnInitialize)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
	PlayerInputComponent->BindAction("ClickChessPiece", EInputEvent::IE_Pressed, this, &AGamePawn::ClickChessPiece);
	PlayerInputComponent->BindAction("MoveChessPiece", EInputEvent::IE_Pressed, this, &AGamePawn::MoveChessPiece);
}

void AGamePawn::ClickChessPiece()
{
	
}

void AGamePawn::MoveChessPiece()
{
	
}

