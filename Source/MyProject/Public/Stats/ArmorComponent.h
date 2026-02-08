// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stats/AttributeComponent.h"
#include "ArmorComponent.generated.h"

UCLASS(ClassGroup = (Attributes), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UArmorComponent : public UAttributeComponent
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void ApplyDamage(float Damage)
    {
        ApplyDelta(-Damage);
    }
    void Apply(float Damage)
    {
        ApplyDelta(Damage);
    }
};