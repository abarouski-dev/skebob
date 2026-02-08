// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "GameFramework/Character.h"
#include "Stats/HealthComponent.h"
#include "Stats/StaminaComponent.h"
#include "Stats/ArmorComponent.h"

UPlayerHUDWidget* UPlayerHUDWidget::Instance = nullptr;

void UPlayerHUDWidget::BindToAttributes(ACharacter* Character)
{
    if (!Character)
        return;

    HealthComp = Character->FindComponentByClass<UHealthComponent>();
    StaminaComp = Character->FindComponentByClass<UStaminaComponent>();
    ArmorComp = Character->FindComponentByClass<UArmorComponent>();

    if (HealthComp)
    {
        HealthComp->OnValueChanged.AddDynamic(this, &UPlayerHUDWidget::OnHealthChanged);
        OnHealthChanged(HealthComp->CurrentValue, HealthComp->MaxValue);
    }

    if (StaminaComp)
    {
        StaminaComp->OnValueChanged.AddDynamic(this, &UPlayerHUDWidget::OnStaminaChanged);
        OnStaminaChanged(StaminaComp->CurrentValue, StaminaComp->MaxValue);
    }

    if (ArmorComp)
    {
        ArmorComp->OnValueChanged.AddDynamic(this, &UPlayerHUDWidget::OnArmorChanged);
        OnArmorChanged(ArmorComp->CurrentValue, ArmorComp->MaxValue);
    }
    if(Instance == nullptr)
    {
        Instance = this;
    }SetWaweValue(FText::FromString("1"));
}

void UPlayerHUDWidget::NativeDestruct()
{
    // Если этот виджет был текущим инстансом — обнуляем его
    if (Instance == this)
    {
        Instance = nullptr;
    }

    // Обязательно вызываем родительскую версию
    Super::NativeDestruct();
}

void UPlayerHUDWidget::OnHealthChanged(float Current, float Max)
{
    if (PB_Health && Max > 0.f)
    {
        PB_Health->SetPercent(Current / Max);
    }
}

void UPlayerHUDWidget::OnStaminaChanged(float Current, float Max)
{
    if (PB_Stamina && Max > 0.f)
    {
        PB_Stamina->SetPercent(Current / Max);
    }
}

void UPlayerHUDWidget::OnArmorChanged(float Current, float Max)
{
    if (PB_Armor && Max > 0.f)
    {
        PB_Armor->SetPercent(Current / Max);
    }
}


void UPlayerHUDWidget::SetWaweValue(const FText& NewText)
{
    if (waweNum != nullptr)
    {
        FText FinalText = FText::Format(FText::FromString("Wave: {0}"), NewText);
        waweNum->SetText(FinalText);
    }
}