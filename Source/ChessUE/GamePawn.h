
#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
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
	class UCameraComponent* PCamera;

	UPROPERTY()
	class USceneComponent* PScene;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ClickChessPiece();

	void MoveChessPiece(float a);
};
