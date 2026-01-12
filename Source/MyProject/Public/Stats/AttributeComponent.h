// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, float, Current, float, Max);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAttributeComponent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MaxValue = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CurrentValue = 100.f;

    UPROPERTY(BlueprintAssignable)
    FOnAttributeChanged OnValueChanged;

    UFUNCTION()
    void SetMaxValue(float NewMax);

    UFUNCTION()
    void SetCurrentValue(float NewValue);

    UFUNCTION()
    void ApplyDelta(float Delta);

protected:
    void Broadcast();
};
