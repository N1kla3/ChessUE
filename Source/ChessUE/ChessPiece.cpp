// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AChessPiece::AChessPiece()
{
	
}

AChessPiece::AChessPiece(const int32 X, const int32 Y)
	: XBoardCoord(X)
	, YBoardCoord(Y)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

FBoardLocation AChessPiece::GetMoveLocation()
{
	return FBoardLocation(XBoardCoord, YBoardCoord);
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

