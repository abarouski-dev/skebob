// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/WeaponPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TwinStickCharacter.h"

AWeaponPickup::AWeaponPickup()
{
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(100.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = CollisionComponent;

    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    PickupMesh->SetupAttachment(RootComponent);
    PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::OnOverlapBegin);
}

void AWeaponPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        ATwinStickCharacter* Player = Cast<ATwinStickCharacter>(OtherActor);
        if (Player)
        {
            Player->AddWeapon(WeaponType, WeaponClass);

            Destroy();
        }
    }
}

