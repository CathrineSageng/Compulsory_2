// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlienShip.generated.h"

class UBoxComponent;

UCLASS()
class COMPULSORY_2_API AAlienShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlienShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UBoxComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	USkeletalMeshComponent* AlienShip;


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
					bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DestroyTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	float XKillPosition;
};
