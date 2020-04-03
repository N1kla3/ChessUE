// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AChessPiece::AChessPiece()
{
	
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AChessPiece::CanMoveToLocation(FBoardLocation cell)
{
	return true;
}

void AChessPiece::Highlight()
{	
	
}

FBoardLocation AChessPiece::GetBoardLocation()
{
	return FBoardLocation(XBoardCoord, YBoardCoord);
}

void AChessPiece::SetBoardLocation(FBoardLocation Location)
{
	XBoardCoord = Location.Key;
	YBoardCoord = Location.Value;
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

