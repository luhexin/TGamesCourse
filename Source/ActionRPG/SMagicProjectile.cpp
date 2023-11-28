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
	//���������ײ
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
	//����Ŀ���� -> ��ײ -> Preset���½���Ϊ��Projectile�������ã�����ħ��������ײ��⡣
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	//Ͷ������������˶�
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 5000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	//������Ч
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
	// ��ը��Ч
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	Destroy();
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	//���⹥���߱��Լ��������˺�
	//��character���Ѿ�����SpawnParams.Instigator = this;
	if(OtherActor && OtherActor != GetInstigator()) {
		//���AttributeComp
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		// �ٴ��пգ�������������ǽ�ڡ����ӵ�û��Ѫ��������
		if(AttributeComp){
			if(AttributeComp->getHealth() >= 20){
				// ħ���������20Ѫ���˺�
				AttributeComp->ApplyHealthChange(-20.0f);
			}
			// ��ը��Ч
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
			// һ������˺������٣����⴩����ɫ��������
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
	// ��ը��Ч
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	Destroy();
}

