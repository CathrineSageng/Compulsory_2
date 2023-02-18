// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo.h"
//#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "AlienShip.h"


// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(50, 10, 10));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::OnOverlap);
	//Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));

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

	//Code from afternoon sessions with Alexander 
	FVector Newlocation = GetActorLocation();
	Newlocation += GetActorForwardVector() * speed * DeltaTime;
	SetActorLocation(Newlocation);

	Timelived += DeltaTime;

	if (Timelived > LifeSpan)
	{
		DestroyBullet();
	}
}

//Code from afternoon sessions with Alexander 
void AAmmo::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Green,
		FString::FString("Never triggers ... " + AActor::GetDebugName(OtherActor))
	);

	if (OtherActor->IsA<AAlienShip>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Green,
			FString::FString("Collide in AAmmo is AAlienShip")
		);
		Cast<AAlienShip>(OtherActor)->DestroyTarget();
		DestroyBullet();
	}
}

//Code from afternoon sessions with Alexander 
void AAmmo::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

