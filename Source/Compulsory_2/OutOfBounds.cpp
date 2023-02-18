// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "OutOfBounds.h"

// Sets default values
AOutOfBounds::AOutOfBounds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(5000, 10, 5000));
}

// Called when the game starts or when spawned
void AOutOfBounds::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOutOfBounds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

