// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KartPawn.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class KARTGAME_API AKartPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKartPawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Kart")
	void SetCanMove(bool bInCanMove);
	
	UFUNCTION(BlueprintPure, Category = "Kart")
	bool CanMove() const { return bCanMove; }
	
	UFUNCTION(BlueprintPure, Category = "Kart")
	FVector GetMovementDirection() const;
	
	void EnterLapZone(int32 ZoneIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Kart|Race")
	void CompleteLap();
	
	UFUNCTION(BlueprintCallable, Category = "Kart|Race")
	void ResetRaceProgress();
	
	UFUNCTION(BlueprintPure, Category = "Kart|Race")
	int32 GetCurrentLap() const { return currentLap; }
	
	UFUNCTION(BlueprintPure, Category = "Kart|Race")
	bool HasFinishedRace() const {return bhasFinishedRace;}

	UFUNCTION(BlueprintPure, Category = "Kart|Race")
	float GetFinishTime() const { return FinishTime; }
	

	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Componets")
	TObjectPtr<USphereComponent> CollisionSphere ;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Componets")
	TObjectPtr<UStaticMeshComponent> WheelFrontLeft;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Componets")
	TObjectPtr<UStaticMeshComponent> WheelFrontRight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Componets")
	TObjectPtr<UStaticMeshComponent> WheelRearLeft;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Componets")
	TObjectPtr<UStaticMeshComponent> WheelRearRight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kart|Components")
	TObjectPtr<UCameraComponent> Camera;
	
	// ---------- Input ----------
	
	UPROPERTY(EditAnywhere, Category = "Kart|Inputs")
	TObjectPtr<UInputMappingContext> KartMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Kart|Inputs")
	TObjectPtr<UInputAction> ThrottleAction;

	UPROPERTY(EditAnywhere, Category = "Kart|Inputs")
	TObjectPtr<UInputAction> SteerAction;

	UPROPERTY(EditAnywhere, Category = "Kart|Input")
	TObjectPtr<UInputAction> DriftAction;

	UPROPERTY(EditAnywhere, Category = "Kart|Input")
	TObjectPtr<UInputAction> JumpAction;

	// ---------- Réglages : déplacement (cm et secondes) ----------
	
	UPROPERTY(EditAnywhere, Category = "Kart|Movement")
	float MaxForwardSpeed = 2500.f;

	UPROPERTY(EditAnywhere, Category = "Kart|Movement")
	float MaxReverseSpeed = 800.f;
	
	UPROPERTY(EditAnywhere, Category = "Kart|Movement")
	float Acceleration = 1500.f;
	
	// Décélération quand on appuie dans le sens opposé à la vitesse
	UPROPERTY(EditAnywhere, Category = "Kart|Movement")
	float BrakeDeceleration = 3000.f;
	
	// Décélération quand on lâche les gaz
	UPROPERTY(EditAnywhere, Category = "Kart|Movement")
	float CoastDeceleration = 800.f;
	
	// Vitesse de rotation en degrés par seconde
	UPROPERTY(EditAnywhere, Category = "Kart|Movement")
	float TurnRate = 100.f;
	
	// En dessous de cette vitesse, le kart ne tourne pas
	UPROPERTY(EditAnywhere, Category = "Kart|Movement")
	float MinSpeedToTurn = 50.f;

	UPROPERTY(EditAnywhere, Category = "Kart|Movement", meta = (ClampMin = "0", ClampMax = "1"))
	float WallSpeedFactor = 0.3f;
	

	
};
