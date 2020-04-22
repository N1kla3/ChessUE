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
	void SetPiece(AChessPiece *piece);
	void DestroyPiece();
	
	FBoardLocation GetBoardLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	int32 Xcoord;

	UPROPERTY()
	int32 Ycoord;

private:
	void InitMesh();

};