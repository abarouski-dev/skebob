// Copyright Epic Games, Inc. All Rights Reserved.


#include "TwinStickNPC.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TwinStickCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TwinStickGameMode.h"
#include "TwinStickPickup.h"
#include "Engine/World.h"
#include "TwinStickNPCDestruction.h"
#include "TimerManager.h"
#include <Variant_TwinStick/AI/SpawnersController.h>
#include "Kismet/GameplayStatics.h"

TArray<ATwinStickNPC*> ATwinStickNPC::NPCs = TArray<ATwinStickNPC*>();

ATwinStickNPC::ATwinStickNPC()
{
	PrimaryActorTick.bCanEverTick = true; // <- 16 ������

	// ensure we spawn an AI controller when we're spawned
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// configure the inherited components
	GetCapsuleComponent()->SetCapsuleRadius(45.0f);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->MaxAcceleration = 1000.0f;
	GetCharacterMovement()->BrakingFriction = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 100.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 250.0f;
	GetCharacterMovement()->AvoidanceWeight = 1.0f;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

}

void ATwinStickNPC::BeginPlay()
{
	Super::BeginPlay();

	// increment the NPC counter so we can cap spawning if necessary
	if (ATwinStickGameMode* GM = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->IncreaseNPCs();
	}

	//count++;
	NPCs.Add(this);
}

void ATwinStickNPC::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// clear the destruction timer
	GetWorld()->GetTimerManager().ClearTimer(DestructionTimer);
}

void ATwinStickNPC::Destroyed()
{
	NPCs.Remove(this);
	//count--;
	// decrease the NPC counter so we can cap spawning if necessary
	if (ATwinStickGameMode* GM = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->DecreaseNPCs();
	}

	if (ActorsToSpawnClass.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("PossibleActorsToSpawn array is empty!"));
		return;
	}

	UWorld* const World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is null"));
		return;
	}

	int32 RandomIndex = FMath::RandRange(0, ActorsToSpawnClass.Num() - 1);

	TSubclassOf<AActor> ClassToSpawn = ActorsToSpawnClass[RandomIndex];

	if (ClassToSpawn != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AActor* SpawnedActor = World->SpawnActor<AActor>(ClassToSpawn, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
		UE_LOG(LogTemp, Warning, TEXT("Spawn Sucesfull"));
	}


	Super::Destroyed();
}

void ATwinStickNPC::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ATwinStickCharacter* PlayerCharacter = Cast<ATwinStickCharacter>(Other))
	{
		if (HitPlayerSound) UGameplayStatics::PlaySoundAtLocation(this, HitPlayerSound, GetActorLocation());
		PlayerCharacter->HandleDamage(1.0f * ASpawnersController::Instance->EnemyDamageMultyplayer, GetActorForwardVector());
	}
}

void ATwinStickNPC::ProjectileImpact(const FVector& ForwardVector, float damage)
{
	float SafeMultiplier = 1.0f;
	if (ASpawnersController::Instance != nullptr && ASpawnersController::Instance->EnemyHPMultyplayer > 0.0f)
	{
		SafeMultiplier = ASpawnersController::Instance->EnemyHPMultyplayer;
	}
	healse -= damage / SafeMultiplier;
	if (healse > 0) 
	{
		if (TakeDamageSound) UGameplayStatics::PlaySoundAtLocation(this, TakeDamageSound, GetActorLocation());
		return;
	}

	if (!bHit && DeathSound) UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());

	// only handle damage if we haven't been hit yet
	if (bHit)
	{
		return;
	}

	// raise the hit flag
	bHit = true;

	// deactivate character movement
	GetCharacterMovement()->Deactivate();

	// award points
	if (ATwinStickGameMode* GM = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->ScoreUpdate(Score);
	}

	// randomly spawn a pickup
	if (FMath::RandRange(0, 100) < PickupSpawnChance)
	{
		AActor* Pickup = GetWorld()->SpawnActor<AActor>(PickupClass[FMath::Rand() % PickupClass.Num()], GetActorTransform());
	}
	
	// spawn the NPC destruction proxy
	ATwinStickNPCDestruction* DestructionProxy = GetWorld()->SpawnActor<ATwinStickNPCDestruction>(DestructionProxyClass, GetActorTransform());

	// hide this actor
	SetActorHiddenInGame(true);

	// disable collision
	SetActorEnableCollision(false);

	// defer destruction
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &ATwinStickNPC::DeferredDestroy, DeferredDestructionTime, false);
}

void ATwinStickNPC::DeferredDestroy()
{
	// destroy this actor
	Destroy();
}
