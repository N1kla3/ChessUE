// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AChessPiece::AChessPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> figure;
		FConstructorStatics()
			: figure(TEXT("/Game/Shape_Cone.Shape_cone"))
		{
		}	
	};

	static FConstructorStatics ChessConstructor;
	
	figScene = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = figScene;

	Figure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("figure"));
	Figure->SetStaticMesh(ChessConstructor.figure.Get());
}

AChessPiece::AChessPiece(int32 X, int32 Y):XBoardCoord(X), YBoardCoord(Y)
{
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

