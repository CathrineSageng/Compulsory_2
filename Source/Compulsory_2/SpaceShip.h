// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "Ammo.h"
#include "SpaceShip.generated.h"

class UStaticMesh;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;

//class FInputActionValue;

UCLASS()
class COMPULSORY_2_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	USkeletalMeshComponent* SpaceShip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	TSubclassOf<AAmmo> BP_Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UBoxComponent* Collider;

	// Code from sessions with Meisam
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputMappingContext* MainInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_RightLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Shoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Reload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Restart;

	// Code from sessions with Meisam
	UFUNCTION(BlueprintCallable, Category = Functions)
	void RightLeft(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable, Category = Functions)
	void Shoot(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable, Category = Functions)
	void Reload(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable, Category = Functions)
	void Restart(const FInputActionValue& val);

	void HitByAlienShip();

	float speed;
	float input;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =Variables)
	int Lives;

	
};
