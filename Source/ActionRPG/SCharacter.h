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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) //����ͼ����ʾ����
	USpringArmComponent* SpringArmComp;//���ڴ�������ͷϵͳ�е�Spring Arm�����ɱۣ����������ʵ��������桢���غ͹۲칦��

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);


	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;//�൱��ǿ��ָ��ΪAActor��UClass, ����ͼ�а�
	
	UPROPERTY(EditAnywhere, Category = "Dash")
	TSubclassOf<AActor> ProjectileDashClass;//�൱��ǿ��ָ��ΪAActor��UClass, ����ͼ�а�

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;//��������ϵͳ
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_PrimaryDash;


	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;//ActorComponent�࣬ʵ�ֽ���
	
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
