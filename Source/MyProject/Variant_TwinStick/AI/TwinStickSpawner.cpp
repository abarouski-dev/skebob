// Copyright Epic Games, Inc. All Rights Reserved.


#include "TwinStickSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "Kismet/GameplayStatics.h"
#include "TwinStickNPC.h"
#include "TwinStickGameMode.h"
#include <Variant_TwinStick/AI/SpawnersController.h>

ATwinStickSpawner::ATwinStickSpawner()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ATwinStickSpawner::StartSpawning()
{

}

void ATwinStickSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// find the recast navmesh actor on the level
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARecastNavMesh::StaticClass(), ActorList);

	if (ActorList.Num() > 0)
	{
		NavData = Cast<ARecastNavMesh>(ActorList[0]);
	} else {

		UE_LOG(LogTemp, Log, TEXT("Could not find recast navmesh"));

	}

	// set up the spawn timer
	//GetWorld()->GetTimerManager().SetTimer(SpawnGroupTimer, this, &ATwinStickSpawner::SpawnNPCGroup, SpawnGroupDelay, true);

	// spawn the first group of NPCs
	//SpawnNPCGroup();
}

void ATwinStickSpawner::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// clear the spawn timers
	//GetWorld()->GetTimerManager().ClearTimer(SpawnGroupTimer);
	GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimer);
}

void ATwinStickSpawner::SpawnNPCGroup()
{
	if (SpawnCount == 0) return;
	UE_LOG(LogTemp, Warning, TEXT("hueta"));
	// reset the group spawn counter
	SpawnCount = 0;

	// check if we're still under the max NPC cap
	if (ATwinStickGameMode* GM = Cast<ATwinStickGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (GM->CanSpawnNPCs())
		{
			GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimer, this, &ATwinStickSpawner::SpawnNPC, ASpawnersController::Instance->SpawnGroupDelay + FMath::RandRange(ASpawnersController::Instance->MinSpawnDelay, ASpawnersController::Instance->MaxSpawnDelay), false);
		}
	}
}

void ATwinStickSpawner::SpawnNPC()
{
	FTransform SpawnTransform;

	// find a random point around the spawner
	FVector SpawnLoc;
	if (UNavigationSystemV1::K2_GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), SpawnLoc, ASpawnersController::Instance->SpawnRadius, NavData))
	{
		SpawnTransform.SetLocation(SpawnLoc);

		// spawn the NPC
		ATwinStickNPC* NPC = GetWorld()->SpawnActor<ATwinStickNPC>(ASpawnersController::Instance->NPCClass[FMath::Rand()% ASpawnersController::Instance->NPCClass.Num()], SpawnTransform);
	}

	// increase the spawn counter
	++SpawnCount;

	// do we still have enemies left to spawn?
	if (SpawnCount < ASpawnersController::Instance->SpawnGroupSize)
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimer, this, &ATwinStickSpawner::SpawnNPC, FMath::RandRange(ASpawnersController::Instance->MinSpawnDelay, ASpawnersController::Instance->MaxSpawnDelay), false);
	}
}
