// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

ABishop::ABishop()
	:AChessPiece()
{
	const TCHAR* PathToModel = L"/Game/Shape_Cone.Shape_Cone";
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(PathToModel);

	FigScene = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = FigScene;

	Figure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("figure"));
	if (VisualAsset.Succeeded())
	{
		Figure->SetStaticMesh(VisualAsset.Object);
	}
	Figure->SetupAttachment(RootComponent);
}

ABishop::ABishop(const int32 X, const int32 Y)
	: AChessPiece(X, Y)
{
	ABishop();
}

FBoardLocation ABishop::GetMoveLocation()
{
	return FBoardLocation(XBoardCoord, YBoardCoord);
}
