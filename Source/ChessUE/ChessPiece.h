// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

UCLASS(Abstract)
class CHESSUE_API AChessPiece : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	int32 XBoardCoord;

	UPROPERTY()
	int32 YBoardCoord;

	UPROPERTY()
	USceneComponent* figScene;
	
	UPROPERTY()
	UStaticMeshComponent* Figure;
	
public:	
	// Sets default values for this actor's properties
	AChessPiece();
	AChessPiece(int32 X, int32 Y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
