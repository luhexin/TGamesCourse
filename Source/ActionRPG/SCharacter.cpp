// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 将相机绑定于该组件上
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");//UE中显示的该控件的名字
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	
	
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);//蒙太奇动画播放系统
		// 0.18s延迟后触发魔法粒子生成
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.18f);

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	// 朝向角色方向，在角色的右手生成
	FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");
	if(CameraComp != nullptr){
		FVector CameraLocation = CameraComp->GetComponentLocation();
		FTransform SpawnTM = FTransform(GetControlRotation(), CameraLocation);
		//FTransform SpawnTM = FTransform(GetActorRotation(), RightHandLoc);
		// 参数设置
		// 此处设置碰撞检测规则为：即使碰撞也总是生成，因为粒子在角色中间生成必然碰撞
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;// 避免自身受伤害
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//SpawnActor参数: 要生成的对象的class、Transform变换属性、生成的相关参数设置
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}

}

void ASCharacter::PrimaryDash()
{
	PlayAnimMontage(AttackAnim);//蒙太奇动画播放系统
		// 0.18s延迟后触发魔法粒子生成
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryDash, this, &ASCharacter::PrimaryDash_TimeElapsed, 0.18f);

}

void ASCharacter::PrimaryDash_TimeElapsed()
{
	// 朝向角色方向，在角色的右手生成
	FVector RightHandLoc = GetMesh()->GetSocketLocation("Muzzle_01");
	if(CameraComp != nullptr){
		FVector CameraLocation = CameraComp->GetComponentLocation();
		FTransform SpawnTM = FTransform(GetControlRotation(), CameraLocation);
		//FTransform SpawnTM = FTransform(GetActorRotation(), RightHandLoc);
		// 参数设置
		// 此处设置碰撞检测规则为：即使碰撞也总是生成，因为粒子在角色中间生成必然碰撞
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;// 避免自身受伤害
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//SpawnActor参数: 要生成的对象的class、Transform变换属性、生成的相关参数设置
		GetWorld()->SpawnActor<AActor>(ProjectileDashClass, SpawnTM, SpawnParams);
	}
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// map keys to functions, BindAxis函数中第一个参数与UE project setting中的Axis mapping一致
	// “UE中调用的名称”，this指针表示移动这个角色，&具体方法实现
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// 绑定按键动作("UE中调用的名称"；触发的时机如按下或释放；对象；具体方法实现)
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryDash", IE_Pressed, this, &ASCharacter::PrimaryDash);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// 交互
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	UE_LOG(LogTemp, Log, TEXT("Health %f"), NewHealth);
	//​UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	// 血量小于0且（包括治疗）血量变化也小于0
	if(NewHealth <= 0){
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}
