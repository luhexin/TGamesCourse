// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->Radius = 550.0f;
	ForceComp->ImpulseStrength = 700.0f;
	ForceComp->bImpulseVelChange = true;
}


// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	ForceComp->FireImpulse();

	/*UE_LOG(LogTemp, Log, TEXT("OnActorHit"));
	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	

	FString CombStr = FString::Printf(TEXT("Hit at %s"), *Hit.ImpactPoint.ToString());*/
	// 获取世界，位置，打印的内容，需要attach的actor，颜色，持续时间，是否有影子
	// DrawDebugString(GetWorld(), Hit.ImpactPoint, CombStr, nullptr, FColor::Green, 2.0f, true);
}