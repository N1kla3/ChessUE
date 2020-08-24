#pragma once

#include "BoardCell.h"
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ChessBoard.h"
#include "GameFramework/Pawn.h"
#include "PieceChooserWidget.h"
#include "GamePawn.generated.h"

UCLASS()
class CHESSUE_API AGamePawn : public APawn
{	GENERATED_BODY()

public:

	AGamePawn();
	UFUNCTION(BlueprintCallable)
	void ChangeIndexCreator(const int Num)
	{
		FigureCreatorIndex = Num;
	}
	UFUNCTION(BlueprintCallable)
	void CreatePieceInGUI();

protected:
	virtual void BeginPlay() override;

	int FigureCreatorIndex;
	
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

	TSubclassOf<UUserWidget> Widget;

	UPROPERTY(BlueprintReadWrite)
	UPieceChooserWidget* ChooserWidget;
	
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

	bool IsTimeToPromotePawn(const FBoardLocation ToMove);
	
	void SwapPlayers();
};
