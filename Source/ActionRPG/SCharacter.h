// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class USAttributeComponent;

UCLASS()
class ACTIONRPG_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) //在蓝图里显示属性
	USpringArmComponent* SpringArmComp;//用于创建摄像头系统中的Spring Arm（弹簧臂），这可用于实现相机跟随、挂载和观察功能

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);


	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;//相当于强制指定为AActor的UClass, 在蓝图中绑定
	
	UPROPERTY(EditAnywhere, Category = "Dash")
	TSubclassOf<AActor> ProjectileDashClass;//相当于强制指定为AActor的UClass, 在蓝图中绑定

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;//动画播放系统
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_PrimaryDash;


	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;//ActorComponent类，实现交互
	
	UFUNCTION(BlueprintCallable)
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();

	UFUNCTION(BlueprintCallable)
	void PrimaryDash();
	void PrimaryDash_TimeElapsed();

	UFUNCTION(BlueprintCallable)
	void PrimaryInteract();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;


};
