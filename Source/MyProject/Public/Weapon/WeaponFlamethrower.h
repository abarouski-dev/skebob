// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "WeaponFlamethrower.generated.h"

UCLASS()
class MYPROJECT_API AWeaponFlamethrower : public ABaseWeapon
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Flamethrower")
    float Range = 500.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Flamethrower")
    float DamageWidth = 150.0f;

protected:
    virtual void Fire() override;
};
