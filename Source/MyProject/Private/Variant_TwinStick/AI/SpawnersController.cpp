// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_TwinStick/AI/SpawnersController.h"
#include "Variant_TwinStick/AI/TwinStickNPC.h"
#include "Variant_TwinStick/AI/TwinStickSpawner.h"
#include "UI/PlayerHUDWidget.h"

ASpawnersController* ASpawnersController::Instance = nullptr;
// Sets default values
ASpawnersController::ASpawnersController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Instance = this;
}

// Called when the game starts or when spawned
void ASpawnersController::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < Spawners.Num(); i++)
	{
		Spawners[i]->SpawnNPCGroup();
	}

	if (UPlayerHUDWidget::Instance != nullptr) UPlayerHUDWidget::Instance->SetWaweValue(FText::FromString(FString::FromInt(waweNumber)));

    ATwinStickNPC::count = 0;
}

void ASpawnersController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("ATwinStickNPC::count: %d"), ATwinStickNPC::count);
	if(ATwinStickNPC::count == 0)    // Add this include at the top of the file
	{
		for (int i = 0; i < Spawners.Num(); i++)
		{
			if(Spawners[i]->SpawnCount == SpawnGroupSize) Spawners[i]->SpawnNPCGroup();
			else return;
		}

		waweNumber++;
		if (UPlayerHUDWidget::Instance != nullptr) UPlayerHUDWidget::Instance->SetWaweValue(FText::FromString(FString::FromInt(waweNumber)));
		SpawnGroupSize += SpawnGroupSizeIncrise;
		EnemyHPMultyplayer += EnemyHPMultyplayerIncrise;
		EnemyDamageMultyplayer += EnemyDamageMultyplayerIncrise;
	}
}
