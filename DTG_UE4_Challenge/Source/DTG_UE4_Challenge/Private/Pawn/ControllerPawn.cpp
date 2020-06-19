// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/ControllerPawn.h"
#include "..\..\Public\Pawn\ControllerPawn.h"

// Sets default values
AControllerPawn::AControllerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AControllerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (pool_type_!= nullptr)
		pool_reference_ = GetWorld()->SpawnActor<AMPool>(pool_type_, FTransform::Identity);
	if (o_type_!= nullptr)
		o_reference_ = GetWorld()->SpawnActor<AOActor>(o_type_, FTransform::Identity);
	if (o_reference_ != nullptr)
		o_reference_->SetActorLocation(FVector(0, 0, 300));

}

void AControllerPawn::SpawnNewMObject()
{
	current_m_object_ = pool_reference_->SpawnMObject(
		FVector(FMath::FRandRange(-200.0f, 1400.0f),
			FMath::FRandRange(-200.0f, 1400.0f),
			500));
}

// Called to bind functionality to input
void AControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Spawn", IE_Pressed,
		this, &AControllerPawn::SpawnNewMObject);
	controller_ = Cast<APlayerController>(GetController());
	//Enable mouse ingame
	if (controller_ != nullptr)
	{
		controller_->bShowMouseCursor = true;
		controller_->bEnableClickEvents = true;
		controller_->bEnableMouseOverEvents = true;
	}
	PlayerInputComponent->BindAction("Click", IE_Pressed,
		this, &AControllerPawn::MouseClicked);
	PlayerInputComponent->BindAction("Click", IE_Released,
		this, &AControllerPawn::MouseRelease);
}

void AControllerPawn::MouseClicked()
{

	FVector direction;
	if (controller_ != nullptr)
	{
		clickresult = controller_->DeprojectMousePositionToWorld(mouse_src_ps, direction);
	}
}

void AControllerPawn::MouseRelease()
{

	if (current_m_object_ == nullptr)
		return;
	FVector direction;
	if (controller_ != nullptr)
	{
		releaseresult = controller_->DeprojectMousePositionToWorld(mouse_dst_ps, direction);
	}
	if (current_m_object_->clicked() && clickresult && releaseresult) {
		FVector forceToAdd = mouse_dst_ps - mouse_src_ps;
		forceToAdd.Z = 0;
		forceToAdd.Normalize();
		current_m_object_->AddForce(forceToAdd);
		current_m_object_->SetClicked(false);
	}
}

