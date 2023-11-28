// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	Health = 100.0f;
	Spirit = 100.0f;
	Score = 0;
}


// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	if(Health < 0) Health = 0;
	
	// 用于判断操作是否成功完成，如角色死亡、特殊机制等情况可能失败
	return true;
}

float USAttributeComponent::getHealth()
{
	return Health;
}

float USAttributeComponent::getSpirit()
{
	return Spirit;
}

void USAttributeComponent::maxHealth()
{
	Health = 100.0f;
}


bool USAttributeComponent::isAlive() const
{
	return Health <= 0.0f;
}

bool USAttributeComponent::DesSpirit(float Delta = 20)
{
	Spirit -= 20.0f;
	if(Spirit < 0){
		Spirit = 0;
		return false;
	}
	return true;
}

bool USAttributeComponent::AddSpirit(float Delta = 100)
{
	Spirit += Delta;
	if(Spirit > 100) Spirit = 100;
	return true;
}

void USAttributeComponent::addScore(float Delta = 100)
{
	Score += Delta;
}

