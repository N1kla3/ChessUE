// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

typedef TPair<int32, int32> FBoardLocation;

UCLASS(Abstract)
class CHESSUE_API AChessPiece : public AActor
{	GENERATED_BODY()

public:
	AChessPiece();
	
	AChessPiece(int32 X, int32 Y);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	int32 XBoardCoord;

	UPROPERTY()
	int32 YBoardCoord;

	UPROPERTY()
	USceneComponent* FigScene;
	
	UPROPERTY()
	UStaticMeshComponent* Figure;
	

public:
	virtual FBoardLocation GetMoveLocation();

	void Highlight();

	FBoardLocation GetBoardLocation();

	void SetBoardLocation(FBoardLocation);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
