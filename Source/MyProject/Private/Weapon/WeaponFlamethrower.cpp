// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponFlamethrower.h"
#include "TwinStickCharacter.h"
#include "TwinStickNPC.h"
#include "Engine/OverlapResult.h"

void AWeaponFlamethrower::Fire()
{
    if (CurrentAmmo <= 0)
    {
        Reload();
        return;
    }

    CurrentAmmo--;

    if (!MyOwner) return;

    FVector Start = GetActorLocation();
    FVector Forward = GetActorForwardVector();
    FVector BoxCenter = Start + (Forward * (Range / 2.0f));
    FVector HalfSize = FVector(Range / 2.0f, DamageWidth, 100.0f);

    TArray<FOverlapResult> OutOverlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(MyOwner);

    bool bHit = GetWorld()->OverlapMultiByChannel(
        OutOverlaps,
        BoxCenter,
        GetActorQuat(),
        ECC_Pawn,
        FCollisionShape::MakeBox(HalfSize),
        Params
    );

    //DrawDebugBox(GetWorld(), BoxCenter, HalfSize, GetActorQuat(), FColor::Red, false, 0.1f);

    if (bHit)
    {
        float TotalDamage = BaseDamage * MyOwner->GetWeaponDamageModifier();

        for (auto& Overlap : OutOverlaps)
        {
            if (ATwinStickNPC* Enemy = Cast<ATwinStickNPC>(Overlap.GetActor()))
            {
                Enemy->ProjectileImpact(Forward, TotalDamage);
            }
        }
    }
    FireParticles();
}
