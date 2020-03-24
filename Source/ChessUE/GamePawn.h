// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GamePawn.generated.h"

UCLASS()
class CHESSUE_API AGamePawn : public APawn
{
	GENERATED_BODY()

public:
	AGamePawn();
	// Sets default values for this pawn's properties
	AGamePawn(const FObjectInitializer& Initialize);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
