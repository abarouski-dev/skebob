// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TwinStickNPC.h"
#include "TwinStickSpawner.generated.h"

class ARecastNavMesh;

/**
 *  A simple NPC spawner for a Twin Stick Shooter game
 */
UCLASS(abstract)
class ATwinStickSpawner : public AActor
{
	GENERATED_BODY()
	
protected:

	/** Type of NPC to spawn */
	
	
	/** Number of NPCs spawned in the current group */

	/** NPC group spawn timer */
	FTimerHandle SpawnGroupTimer;

	/** NPC spawn timer */
	FTimerHandle SpawnNPCTimer;

	/** Pointer to the recast nav mesh actor, used to provide NPC spawn locations */
	TObjectPtr<ARecastNavMesh> NavData;

public:	

	int32 SpawnCount = 1;
	/** Constructor */
	ATwinStickSpawner();

	static void StartSpawning();
	/** Spawns a new NPC group */
	void SpawnNPCGroup();

protected:

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Gameplay cleanup */
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

protected:


	/** Spawns an individual NPC */
	void SpawnNPC();

};
