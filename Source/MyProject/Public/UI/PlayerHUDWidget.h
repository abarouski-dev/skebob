// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerHUDWidget.generated.h"

class UHealthComponent;
class UStaminaComponent;
class UArmorComponent;

UCLASS()
class MYPROJECT_API UPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    // Bind to UMG widgets
    UPROPERTY(meta = (BindWidget))
    UProgressBar* PB_Health;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* PB_Stamina;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* PB_Armor;

    // Call this after widget creation
    UFUNCTION(BlueprintCallable)
    void BindToAttributes(ACharacter* Character);

protected:

    UFUNCTION()
    void OnHealthChanged(float Current, float Max);

    UFUNCTION()
    void OnStaminaChanged(float Current, float Max);

    UFUNCTION()
    void OnArmorChanged(float Current, float Max);

private:

    UPROPERTY()
    UHealthComponent* HealthComp;

    UPROPERTY()
    UStaminaComponent* StaminaComp;

    UPROPERTY()
    UArmorComponent* ArmorComp;
};
