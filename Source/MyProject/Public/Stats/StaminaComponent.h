// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stats/AttributeComponent.h"
#include "StaminaComponent.generated.h"

UCLASS(ClassGroup = (Attributes), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UStaminaComponent : public UAttributeComponent
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void Consume(float Amount)
    {
        ApplyDelta(-Amount);
    }

    UFUNCTION()
    void Restore(float Amount)
    {
        ApplyDelta(Amount);
    }
};