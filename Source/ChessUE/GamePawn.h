#pragma once

#include "BoardCell.h"
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ChessBoard.h"
#include "GameFramework/Pawn.h"
#include "GamePawn.generated.h"

UCLASS()
class CHESSUE_API AGamePawn : public APawn
{	GENERATED_BODY()

public:

	AGamePawn();


protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bIsCLicked;
	
	UPROPERTY(EditAnywhere)
	class UCameraComponent* PCamera;

	UPROPERTY(EditAnywhere)
	class USceneComponent* PScene;

	UPROPERTY()
	AChessPiece* CurrentChessPieceFocus;

	UPROPERTY()
	ABoardCell* CurrentCellFocus;

	UPROPERTY()
	AChessBoard* Board;

	TBasicArray<FBoardLocation> CurrFigureMoves;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void ClickChessPiece();

	void MoveChessPiece(float a);

	void MoveFigureToCeil();

	TBasicArray<FBoardLocation>& GetOccupiedLocations();

	void TraceForChessPiece(const FVector& Start, const FVector& End);

	void TraceForCeil(const FVector& Start, const FVector& End);

	void FindChessBoard();
};
