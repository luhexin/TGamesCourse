// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FHitResult Hit; // 检测结果


	FVector EyeLocation; // 角色眼睛位置
	FRotator EyeRotation; // 角色视线方向
	AActor* MyOwner = GetOwner(); // 获取控制角色
	// 将玩家视线的位置和方向输出到EyeLocation和EyeRotation
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	// 沿着视线方向，模型的眼睛位置开始1000cm距离的点为终点
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	FCollisionObjectQueryParams ObjectQueryParams; // 查询参数
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); // 选择查询场景动态对象

	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	// 从判断结果中获取检测到的Actor，没检测到则为空
	AActor* HitActor = Hit.GetActor();
	if(HitActor){
		// 如果检测到actor不为空，再判断actor有没有实现SGameplayInterface类
		if(HitActor->Implements<USGameplayInterface>()){
			// 我们定义的Interact()传入为Pawn类型，因此做类型转换
			APawn* MyPawn = Cast<APawn>(MyOwner);
			// 多态，根据传入的HitActor调用相应函数。HitActor有接口的具体实现
			// 第一个参数不能为空，所以外层已经判空；第二个参数是我们自定义的，暂时没有影响，可以不判空
			ISGameplayInterface::Execute_Interact(HitActor, MyPawn);//接口设置Interact(APawn* InstigatorPawn);
			// 用于debug，绘制这条碰撞检测的线，绿色
			DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Green, false, 3);
		}
	} else{ DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 3); }

}

