// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo.h"
#include "Components/SphereComponent.h"
#include "AlienShip.h"


// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitSphereRadius(10.f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::OnOverlap);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	LaserBeam = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LaserBeam"));
	LaserBeam->SetupAttachment(GetRootComponent());
	LaserBeam->SetRelativeLocation(FVector(0, 0, 0));

	speed = 2000.f;
	Timelived = 0.f;
	LifeSpan = 10.f;

}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Newlocation = GetActorLocation();
	Newlocation += GetActorForwardVector() * speed * DeltaTime;
	SetActorLocation(Newlocation);

	Timelived += DeltaTime;

	if (Timelived > LifeSpan)
	{
		DestroyBullet();
	}
}

void AAmmo::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AAlienShip>())
	{
		//Cast<AAlienShip>(OtherActor)->DestroyTarget();
		DestroyBullet();
	}
}

void AAmmo::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

