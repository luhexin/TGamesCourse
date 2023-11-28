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
	FHitResult Hit; // �����


	FVector EyeLocation; // ��ɫ�۾�λ��
	FRotator EyeRotation; // ��ɫ���߷���
	AActor* MyOwner = GetOwner(); // ��ȡ���ƽ�ɫ
	// ��������ߵ�λ�úͷ��������EyeLocation��EyeRotation
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	// �������߷���ģ�͵��۾�λ�ÿ�ʼ1000cm����ĵ�Ϊ�յ�
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	FCollisionObjectQueryParams ObjectQueryParams; // ��ѯ����
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); // ѡ���ѯ������̬����

	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	// ���жϽ���л�ȡ��⵽��Actor��û��⵽��Ϊ��
	AActor* HitActor = Hit.GetActor();
	if(HitActor){
		// �����⵽actor��Ϊ�գ����ж�actor��û��ʵ��SGameplayInterface��
		if(HitActor->Implements<USGameplayInterface>()){
			// ���Ƕ����Interact()����ΪPawn���ͣ����������ת��
			APawn* MyPawn = Cast<APawn>(MyOwner);
			// ��̬�����ݴ����HitActor������Ӧ������HitActor�нӿڵľ���ʵ��
			// ��һ����������Ϊ�գ���������Ѿ��пգ��ڶ��������������Զ���ģ���ʱû��Ӱ�죬���Բ��п�
			ISGameplayInterface::Execute_Interact(HitActor, MyPawn);//�ӿ�����Interact(APawn* InstigatorPawn);
			// ����debug������������ײ�����ߣ���ɫ
			DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Green, false, 3);
		}
	} else{ DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 3); }

}

