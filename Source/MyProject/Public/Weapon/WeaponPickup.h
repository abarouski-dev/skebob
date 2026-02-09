// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/BaseWeapon.h"
#include "WeaponPickup.generated.h"

class ATwinStickCharacter;

UCLASS()
class MYPROJECT_API AWeaponPickup : public AActor
{
    GENERATED_BODY()

public:
    AWeaponPickup();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* PickupMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    TSubclassOf<class ABaseWeapon> WeaponClass;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
