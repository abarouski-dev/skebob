// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "WeaponProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AWeaponProjectile : public ABaseWeapon
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Shooting")
    TSubclassOf<class ATwinStickProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Shooting")
    float MuzzleOffset = 100.0f;

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundBase* FireSound;

protected:
    virtual void Fire() override;
};
