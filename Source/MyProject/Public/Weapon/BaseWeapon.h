// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    None,
    Pistol,
    Rifle,
    Flamethrower
};

UCLASS()
class MYPROJECT_API ABaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ABaseWeapon();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    EWeaponType WeaponType;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float BaseDamage;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float TimeBetweenShots = 0.2f;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    int32 MaxAmmo = 30;

    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float ReloadTime = 1.5f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponSocketName = TEXT("DefaultWeaponSocket");

    class ATwinStickCharacter* MyOwner;

    void StartFire();
    void StopFire();

    void ResetReloadState();

    int32 CurrentAmmo;

protected:
    bool bIsReloading = false;
    FTimerHandle TimerHandle_HandleFiring;
    FTimerHandle TimerHandle_Reload;

    virtual void BeginPlay() override;

    virtual void Fire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Effects")
	void FireParticles();
    UFUNCTION(BlueprintImplementableEvent)
    void EndParticle();
    void Reload();
    void FinishReload();
};
