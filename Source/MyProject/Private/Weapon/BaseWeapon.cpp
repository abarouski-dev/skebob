#include "Weapon/BaseWeapon.h"
#include "TwinStickCharacter.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ABaseWeapon::ABaseWeapon()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = Mesh;
    Mesh->SetCollisionProfileName(FName("NoCollision"));
}

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    CurrentAmmo = MaxAmmo;
}

void ABaseWeapon::StartFire()
{
    if (bIsReloading) return;

    Fire();

    GetWorldTimerManager().SetTimer(TimerHandle_HandleFiring, this, &ABaseWeapon::Fire, TimeBetweenShots, true);

    if (WeaponType == EWeaponType::Flamethrower)
    {
        PlayFlamethrowerLoop(true);
    }
}

void ABaseWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(TimerHandle_HandleFiring);
    EndParticle();

    if (WeaponType == EWeaponType::Flamethrower)
    {
        PlayFlamethrowerLoop(false);
    }
}

void ABaseWeapon::Fire()
{
    if (CurrentAmmo <= 0)
    {
        Reload();
        return;
    }
    
    FireParticles();
    CurrentAmmo--;
}

void ABaseWeapon::Reload()
{
    if (bIsReloading) return;
    EndParticle();

    bIsReloading = true;

    StopFire();

    UE_LOG(LogTemp, Warning, TEXT("Reloading... Time: %f"), ReloadTime);

    GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &ABaseWeapon::FinishReload, ReloadTime, false);
}

void ABaseWeapon::FinishReload()
{
    CurrentAmmo = MaxAmmo;
    bIsReloading = false;

    if (ATwinStickCharacter::IsPressed) 
    {
        StartFire();
    }

    UE_LOG(LogTemp, Warning, TEXT("Reload Finished! Ammo: %d"), CurrentAmmo);
}

void ABaseWeapon::ResetReloadState()
{
    if (GetWorld())
    {
        GetWorldTimerManager().ClearTimer(TimerHandle_Reload);
        GetWorldTimerManager().ClearTimer(TimerHandle_HandleFiring);
    }

    bIsReloading = false;
    CurrentAmmo = MaxAmmo;
}

void ABaseWeapon::PlayFlamethrowerLoop(bool bStart)
{
    if (bStart)
    {
        if (ContinuousFireSound && !FireAudioComp)
        {
            FireAudioComp = UGameplayStatics::SpawnSoundAttached(ContinuousFireSound, RootComponent);
        }
        else if (FireAudioComp)
        {
            FireAudioComp->Play();
        }
    }
    else
    {
        if (FireAudioComp)
        {
            FireAudioComp->Stop();
        }
    }
}