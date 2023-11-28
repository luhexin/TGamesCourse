// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

// 发起者，控件拥有者，改变后的血量，变化值
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Spirit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	int Score;


public:	
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	float getHealth();
	float getSpirit();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void maxHealth();

	UFUNCTION()
	bool isAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool DesSpirit(float Delta);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool AddSpirit(float Delta);


	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void addScore(float Delta);
};
