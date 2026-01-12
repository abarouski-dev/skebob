// Fill out your copyright notice in the Description page of Project Settings.


#include "Stats/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAttributeComponent::SetMaxValue(float NewMax)
{
    MaxValue = FMath::Max(1.f, NewMax);
    CurrentValue = FMath::Clamp(CurrentValue, 0.f, MaxValue);
    Broadcast();
}

void UAttributeComponent::SetCurrentValue(float NewValue)
{
    CurrentValue = FMath::Clamp(NewValue, 0.f, MaxValue);
    Broadcast();
}

void UAttributeComponent::ApplyDelta(float Delta)
{
    CurrentValue = FMath::Clamp(CurrentValue + Delta, 0.f, MaxValue);
    Broadcast();
}

void UAttributeComponent::Broadcast()
{
    OnValueChanged.Broadcast(CurrentValue, MaxValue);
}

