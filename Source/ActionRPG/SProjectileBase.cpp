// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ASProjectileBase::ASProjectileBase()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	//在项目设置 -> 碰撞 -> Preset中新建名为“Projectile”的配置，用于魔法粒子碰撞检测。
	SphereComp->SetCollisionProfileName("DashProjectile");
	RootComponent = SphereComp;


	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);


	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 8000;
}


void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

// _Implementation from it being marked as BlueprintNativeEvent
void ASProjectileBase::Explode_Implementation()
{
	
	if(ensure(!IsPendingKill())){
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}


