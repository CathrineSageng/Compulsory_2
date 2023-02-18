// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShip.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->InitBoxExtent(FVector(500, 500, 200));
	Collider->SetRelativeLocation(FVector(0, 0, 0));
	SetRootComponent(Collider);

	SpaceShip = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SpaceShip"));
	SpaceShip->SetRelativeLocation(FVector(0, 0, 0));
	SpaceShip->SetupAttachment(GetRootComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 1500.f;
	SpringArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	speed = 50;
	input = 0;
	ammo = 20;
	MaxAmmo = 30;
	Lives = 5;
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	// Code from sessions with Meisam
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(MainInput, 0);
		}
	}
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FVector(0, input * speed, 0), true);
	
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Code from sessions with Meisam
	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhanceInputCom->BindAction(IA_RightLeft, ETriggerEvent::Started, this, &ASpaceShip::RightLeft);
		EnhanceInputCom->BindAction(IA_RightLeft, ETriggerEvent::Completed, this, &ASpaceShip::RightLeft);
		EnhanceInputCom->BindAction(IA_Shoot, ETriggerEvent::Started, this, &ASpaceShip::Shoot);
		EnhanceInputCom->BindAction(IA_Reload, ETriggerEvent::Started, this, &ASpaceShip::Reload);
		EnhanceInputCom->BindAction(IA_Restart, ETriggerEvent::Started, this, &ASpaceShip::Restart);
	}
}

void ASpaceShip::RightLeft(const FInputActionValue& val)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Green, FString::FString("Value: " + val.ToString()));
	input = val.GetMagnitude();
}

//Code from afternoon sessions with Alexander 
void ASpaceShip::Shoot(const FInputActionValue& val)
{
	if (ammo > 0)
	{
		ammo--;

		GetWorld()->SpawnActor<AActor>(BP_Ammo, GetActorLocation()
			+ FVector(30.f, 0.f, 70.f), GetActorRotation());
	}
}

void ASpaceShip::Reload(const FInputActionValue& val)
{
}

void ASpaceShip::Restart(const FInputActionValue& val)
{
}


void ASpaceShip::HitByAlienShip()
{
	Lives--;
	if (Lives <= 0)
	{
		//To do game over 
	}
}




