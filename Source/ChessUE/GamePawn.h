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
	class UCameraComponent* PblackCamera;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* PwhiteCamera;
	
	UPROPERTY(EditAnywhere)
	class USceneComponent* PScene;

	UPROPERTY()
	AChessPiece* CurrentChessPieceFocus;

	UPROPERTY()
	ABoardCell* CurrentCellFocus;

	UPROPERTY()
	AChessBoard* Board;

	TEnumAsByte<FigureColor> CurPlayerSide;
	
	TArray<FBoardLocation> CurrFigureMoves;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void ClickChessPiece();

	void MoveChessPiece(float a);

	void MoveFigureToCeil();

	TArray<FBoardLocation>& GetOccupiedLocations();

	void TraceForChessPiece(const FVector& Start, const FVector& End);

	void TraceForCeil(const FVector& Start, const FVector& End);

	void FindChessBoard();

	void HandleChessPiece();
	void HandleChessPawn(const FBoardLocation ToMove);

	void IncreaseMoveIfRook();
	void IncreaseMoveIfKing();
	void MakeCastlingIfNeeded(const FBoardLocation ToMoveLocation);
	
	void SwapPlayers();
};
