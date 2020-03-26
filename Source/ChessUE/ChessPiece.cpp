// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AChessPiece::AChessPiece()
{
	
}

AChessPiece::AChessPiece(int32 X, int32 Y)
	: XBoardCoord(X)
	, YBoardCoord(Y)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const TCHAR* PathToModel = L"/Game/Shape_Cone.Shape_cone";
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(PathToModel);
	
	FigScene = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = FigScene;

	Figure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("figure"));
    if (VisualAsset.Succeeded())
    {
		Figure->SetStaticMesh(VisualAsset.Object);
    }
	
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

FBoardLocation AChessPiece::GetMoveLocation()
{
	return FBoardLocation();
}

FBoardLocation AChessPiece::GetBoardLocation()
{
	return FBoardLocation();
}

void AChessPiece::SetBoardLocation(FBoardLocation Location)
{
	
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

