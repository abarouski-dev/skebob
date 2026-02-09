// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponProjectile.h"
#include "TwinStickProjectile.h"
#include "TwinStickCharacter.h"
#include "Kismet/GameplayStatics.h"

void AWeaponProjectile::Fire()
{
    if (CurrentAmmo <= 0)
    {
        Reload();
        return;
    }

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

        ProjectileTransform.SetRotation(MyOwner->GetActorRotation().Quaternion());

        FVector ProjectileLocation = ProjectileTransform.GetLocation() + ProjectileTransform.GetRotation().RotateVector(FVector::ForwardVector * MuzzleOffset);
        ProjectileTransform.SetLocation(ProjectileLocation);

        ATwinStickProjectile* Projectile = GetWorld()->SpawnActor<ATwinStickProjectile>(ProjectileClass, ProjectileTransform);

        if (Projectile)
        {
            Projectile->damage = BaseDamage * MyOwner->GetWeaponDamageModifier();
        }

        if (FireSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
        }

        FireParticles();
    }
}
