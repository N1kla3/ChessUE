// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardCell.generated.h"

UCLASS()
class CHESSUE_API ABoardCell : public AActor
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY()
	int32 Xcoord;

	UPROPERTY()
	int32 Ycoord;


	UPROPERTY()
	USceneComponent* URoot;

	UPROPERTY()
	UStaticMeshComponent* UCellMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABoardCell();

	ABoardCell(int32 X, int32 Y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void InitMesh();

};