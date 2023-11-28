// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASDashProjectile::ASDashProjectile()
{


	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.f;
}


void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ASDashProjectile::Explode, DetonateDelay);
}


void ASDashProjectile::Explode_Implementation()
{
	// 可能有碰到障碍物提前爆炸的情况，因此要清除Timer防止被调用两次
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	// 爆炸特效
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	// 粒子爆炸后关闭系统、停止移动、停止碰撞
	EffectComp->DeactivateSystem();
	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	// 到传送时间后，触发传送
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASDashProjectile::TeleportInstigator, TeleportDelay);

}


void ASDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if(ensure(ActorToTeleport)){
		// Keep instigator rotation or it may end up jarring
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);

	}

	// Now we're ready to destroy self
	Destroy();
}
