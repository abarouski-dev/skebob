// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProjectile.h"
#include "TwinStickProjectile.h"
#include "TwinStickCharacter.h"

void AWeaponProjectile::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing projectile weapon! Current ammo:"));
    if (CurrentAmmo <= 0)
    {
        Reload();
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("222222222222222"));
    if (ProjectileClass && MyOwner)
    {
        CurrentAmmo--;

        //FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * MuzzleOffset);
        //FRotator SpawnRotation = GetActorRotation();

        //FActorSpawnParameters SpawnParams;
        //SpawnParams.Owner = MyOwner;
        //SpawnParams.Instigator = MyOwner;

        FTransform ProjectileTransform = GetActorTransform();

        ProjectileTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

        FVector ProjectileLocation = ProjectileTransform.GetLocation() + ProjectileTransform.GetRotation().RotateVector(FVector::ForwardVector * MuzzleOffset);
        ProjectileTransform.SetLocation(ProjectileLocation);
        ATwinStickProjectile* Projectile = GetWorld()->SpawnActor<ATwinStickProjectile>(ProjectileClass, ProjectileTransform);

        if (Projectile)
        {
            float BonusDamage = MyOwner->GetWeaponDamageModifier(WeaponType);
            Projectile->damage = 1.0f + BonusDamage;
        }
    }
}
