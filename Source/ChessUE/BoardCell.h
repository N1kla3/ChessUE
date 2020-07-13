#pragma once

#include "ChessPiece.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BoardCell.generated.h"

typedef TPair<int32, int32> FBoardLocation;

UCLASS()
class CHESSUE_API ABoardCell : public AActor
{
	GENERATED_BODY()
	
public:		

	UPROPERTY()
	USceneComponent* URoot;

	UPROPERTY()
	UStaticMeshComponent* UCellMesh;

private:

	UPROPERTY()
	AChessPiece* piece = nullptr;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABoardCell();

	void SetBoardLocation(FBoardLocation);
	void SetPiece(AChessPiece *piece, TEnumAsByte<FigureColor> Color);
	AChessPiece* GetPiece();
	void DestroyPiece();
	
	FBoardLocation GetBoardLocation();
	void SwapBetweenColors();
	void InitColor(TEnumAsByte<FigureColor> Color);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	int32 Xcoord;

	UPROPERTY()
	int32 Ycoord;

	TEnumAsByte<FigureColor> Color;
	bool IsColorChanger;

	UPROPERTY()
	UMaterialInterface* M_White;
	UPROPERTY()
	UMaterialInterface* M_Black;
	UPROPERTY()
	UMaterialInterface* M_Green;
private:
	void InitMesh();

};