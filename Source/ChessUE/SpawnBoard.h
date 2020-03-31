// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBoard.generated.h"

UCLASS()
class CHESSUE_API ASpawnBoard : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	float Xspace;

	UPROPERTY()
	float Yspace;

	UPROPERTY()
	USceneComponent* URoot;
	
	// Sets default values for this actor's properties
	ASpawnBoard();

public:	
	virtual void Tick(float DeltaTime) override;
	// Called every frame
	void SpawnFigures();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
