// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

class USphereComponent;
UCLASS()
class ACTIONRPG_API ASDashProjectile : public ASProjectileBase{
	GENERATED_BODY()

protected:


	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;//¥´ÀÕ—”≥Ÿ

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;//±¨’®—” ±n√Î∫Û±¨’®

	// Handle to cancel timer if we already hit something
	FTimerHandle TimerHandle_DelayedDetonate;

	// Base class using BlueprintNativeEvent, we must override the _Implementation not the Explode()
	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void BeginPlay() override;

public:

	ASDashProjectile();
};
