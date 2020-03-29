// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePawn.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


AGamePawn::AGamePawn()
{
	bIsCLicked = false;
	PScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = PScene;

	PCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	PCamera->SetupAttachment(RootComponent);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


void AGamePawn::BeginPlay()
{
	Super::BeginPlay();
}


void AGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(CurrentChessPieceFocus)
	{
		CurrentChessPieceFocus->Highlight();
	}
	
}


void AGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("ClickChessPiece", EInputEvent::IE_Pressed, this, &AGamePawn::ClickChessPiece);
	PlayerInputComponent->BindAxis("MoveChessPiece", this, &AGamePawn::MoveChessPiece);
}

void AGamePawn::ClickChessPiece()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		if (CurrentChessPieceFocus) 
		{
			//some move code
			CurrentChessPieceFocus = nullptr;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		}
		else
		{
			FVector Start, Dir;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			FVector End = Start + (Dir * 8000.0f);
			TraceForChessPiece(Start, End);
		}
	}	
}

void AGamePawn::MoveChessPiece(float a)
{
	
	if (CurrentChessPieceFocus != NULL)
	{	//debug
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("fff"));
	}
}

void AGamePawn::TraceForChessPiece(const FVector& Start, const FVector& End)
{
	FHitResult FigureHit;
	GetWorld()->LineTraceSingleByChannel(FigureHit, Start, End, ECC_Visibility);

	if(FigureHit.Actor.IsValid())
	{
		AChessPiece* HitPiece = Cast<AChessPiece>(FigureHit.Actor.Get());

		if(CurrentChessPieceFocus != HitPiece)
		{
		
			CurrentChessPieceFocus = HitPiece;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("find new"));
			
		}
		else if (CurrentChessPieceFocus)
		{
			//debug
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("oldddd"));
		}
	}
}

