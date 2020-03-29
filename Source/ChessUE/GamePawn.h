#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ChessPiece.h"
#include "GameFramework/Pawn.h"
#include "GamePawn.generated.h"

UCLASS()
class CHESSUE_API AGamePawn : public APawn
{
	GENERATED_BODY()

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
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ClickChessPiece();

	void MoveChessPiece(float a);

	void TraceForChessPiece(const FVector& Start, const FVector& End);
};
