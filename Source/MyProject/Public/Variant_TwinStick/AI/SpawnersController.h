// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnersController.generated.h"

class ATwinStickSpawner;
class ATwinStickNPC;
class UPlayerHUDWidget;

UCLASS()
class MYPROJECT_API ASpawnersController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnersController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnNPCGroup();

public:
	static ASpawnersController* Instance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UPlayerHUDWidget* widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawners")
	TArray<ATwinStickSpawner*> Spawners;

	UPROPERTY(EditAnywhere, Category = "NPC Spawner")
	TArray<TSubclassOf<ATwinStickNPC>> NPCClass;

	/** Time delay between enemy group spawns */
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 20, Units = "s"))
	float SpawnGroupDelay = 5.0f;

	/** Min time delay between individual NPC spawns */
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 2, Units = "s"))
	float MinSpawnDelay = 0.33f;

	/** Max time delay between individual NPC spawns */
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 2, Units = "s"))
	float MaxSpawnDelay = 0.66f;

	/** Radius around the spawner where it can spawn NPCs */
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 20, Units = "cm"))
	float SpawnRadius = 600.0f;

	/** Number of NPCs to spawn per group */
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 10))
	int32 SpawnGroupSize = 3; 
	
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 10))
	int32 SpawnGroupSizeIncrise = 1;
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 10))
	float EnemyHPMultyplayer = 1; 
	
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 10))
	float EnemyHPMultyplayerIncrise = 0.25f;
	
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 10))
	float EnemyDamageMultyplayer = 1; 
	
	UPROPERTY(EditAnywhere, Category = "NPC Spawner", meta = (ClampMin = 0, ClampMax = 10))
	float EnemyDamageMultyplayerIncrise = 0.25f;

	int waweNumber = 1;
	
	
	virtual void Tick(float DeltaTime) override;
};
