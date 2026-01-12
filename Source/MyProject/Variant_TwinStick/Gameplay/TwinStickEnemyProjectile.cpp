// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_TwinStick/Gameplay/TwinStickEnemyProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TwinStickCharacter.h"

// Sets default values
ATwinStickEnemyProjectile::ATwinStickEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	// this actor will be destroyed automatically once InitialLifeSpan expires
	InitialLifeSpan = 2.0f;

	// create the collision sphere and set it as the root component
	RootComponent = CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));

	CollisionSphere->SetSphereRadius(35.0f);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Block);

	// create the mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionProfileName(FName("NoCollision"));

	// create the projectile movement comp. No need to attach it because it's not a scene component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 15000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bRotationRemainsVertical = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->bForceSubStepping = true;

	ProjectileMovement->OnProjectileStop.AddDynamic(this, &ATwinStickEnemyProjectile::OnProjectileStop);
}
void ATwinStickEnemyProjectile::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// have we hit a NPC?
	if (ATwinStickCharacter* Character = Cast<ATwinStickCharacter>(Other))
	{
		// tell the NPC it's been hit
		Character->HandleDamage(1.0f, GetActorForwardVector());

		// destroy this projectile
		Destroy();
	}
}

void ATwinStickEnemyProjectile::OnProjectileStop(const FHitResult& ImpactResult)
{
	// destroy this actor immediately
	Destroy();
}

