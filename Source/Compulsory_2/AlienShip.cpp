// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo.h"
#include "SpaceShip.h"
#include "Components/BoxComponent.h"
#include "AlienShip.h"

// Sets default values
AAlienShip::AAlienShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Code from afternoon sessions with Alexander 
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(150, 150, 100));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAlienShip::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));

	AlienShip = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AlienShip"));
	AlienShip->SetupAttachment(GetRootComponent());
	AlienShip->SetRelativeLocation(FVector(0, 0, 0));

	MovementSpeed = 350;
	RotationSpeed = 1.f;
	XKillPosition = -200.f;
}

// Called when the game starts or when spawned
void AAlienShip::BeginPlay()
{
	Super::BeginPlay();
	//Code from afternoon sessions with Alexander 
	RotationSpeed = FMath::RandRange(0.5f, 1.5f);
	MovementSpeed += FMath::RandRange(0, 250);
}

// Called every frame
void AAlienShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Code from afternoon sessions with Alexander 
	FVector NewLocation = GetActorLocation();
	NewLocation += FVector(-1, 0, 0) * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	SetActorRotation(GetActorRotation() + FRotator(0, RotationSpeed, 0));

	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}

}

//Code from afternoon sessions with Alexander 
void AAlienShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Green, 
		FString::FString("Collide in AAlienShip: " + AActor::GetDebugName(OtherActor))
	);

	if (OtherActor->IsA<ASpaceShip>())
	{
		Cast<ASpaceShip>(OtherActor)->HitByAlienShip();
		DestroyTarget();
	}

	if (OtherActor->IsA<AAmmo>())
	{
		DestroyTarget();
		Cast<AAmmo>(OtherActor)->DestroyBullet();
	}
}

//Code from afternoon sessions with Alexander 
void AAlienShip::DestroyTarget()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

