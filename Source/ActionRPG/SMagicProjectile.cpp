// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//球体计算碰撞
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	//在项目设置 -> 碰撞 -> Preset中新建名为“Projectile”的配置，用于魔法粒子碰撞检测。
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	//投射体控制球体运动
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 5000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	//粒子特效
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyTimeHandle, this, &ASMagicProjectile::DestroySelf, 5.0f);
}

void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 爆炸特效
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	Destroy();
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	//避免攻击者被自己的粒子伤害
	//在character里已经设置SpawnParams.Instigator = this;
	if(OtherActor && OtherActor != GetInstigator()) {
		//获得AttributeComp
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		// 再次判空，可能碰到的是墙壁、箱子等没有血量的物体
		if(AttributeComp){
			if(AttributeComp->getHealth() >= 20){
				// 魔法粒子造成20血量伤害
				AttributeComp->ApplyHealthChange(-20.0f);
			}
			// 爆炸特效
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
			// 一旦造成伤害就销毁，避免穿过角色继续计算
			Destroy();
		}
	}
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASMagicProjectile::DestroySelf()
{
	// 爆炸特效
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	Destroy();
}

