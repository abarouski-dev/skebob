#include "Weapon/BaseWeapon.h"
#include "TwinStickCharacter.h"
#include "TimerManager.h"

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
}

void ABaseWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(TimerHandle_HandleFiring);
}

void ABaseWeapon::Fire()
{
    if (CurrentAmmo <= 0)
    {
        Reload();
        return;
    }

    CurrentAmmo--;
}

void ABaseWeapon::Reload()
{
    if (bIsReloading) return;

    bIsReloading = true;

    StopFire();

    UE_LOG(LogTemp, Warning, TEXT("Reloading... Time: %f"), ReloadTime);

    GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &ABaseWeapon::FinishReload, ReloadTime, false);
}

void ABaseWeapon::FinishReload()
{
    CurrentAmmo = MaxAmmo;
    bIsReloading = false;

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