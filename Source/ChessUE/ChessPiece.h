// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

UCLASS(Abstract)
class CHESSUE_API AChessPiece : public AActor
{
	GENERATED_BODY()
private:
	int32 XBoardCoord;
	int32 YBoardCoord;
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
