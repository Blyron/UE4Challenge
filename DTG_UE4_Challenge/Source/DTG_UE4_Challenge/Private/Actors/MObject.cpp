// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MObject.h"
#include "Actors/OActor.h"

// Sets default values
AMObject::AMObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh_->OnComponentHit.AddDynamic(this, &AMObject::OnComponentHit);
	mesh_->OnClicked.AddDynamic(this, &AMObject::OnClicked);
	RootComponent = mesh_;
	audio_ = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	audio_->SetupAttachment(RootComponent);
}

void AMObject::ActiveObject(bool active)
{
	SetActorEnableCollision(active);
	SetActorHiddenInGame(!active);
	Cast<UPrimitiveComponent>(RootComponent)->SetSimulatePhysics(active);
	active_ = active;
}

void AMObject::DisableObject()
{
	ActiveObject(false);
}

void AMObject::AddForce(FVector forceToAdd)
{
	Cast<UPrimitiveComponent>(RootComponent)->AddImpulse(forceToAdd * force_intensity_);
	if (!GetWorldTimerManager().IsTimerActive(timer_)) {
		GetWorldTimerManager().SetTimer(timer_, this,
			&AMObject::DisableObject, time_until_dissapear_post_iteraction_, false); 
	}
}

bool AMObject::active()
{
	return active_;
}

void AMObject::SetClicked(bool clicked)
{
	clicked_ = clicked;
}

bool AMObject::clicked()
{
	return clicked_;
}

// Called when the game starts or when spawned
void AMObject::BeginPlay()
{
	Super::BeginPlay();
	ActiveObject(false);
	SetClicked(false);
}

void AMObject::OnComponentHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	AOActor* ptr = Cast<AOActor>(OtherActor);
	if (ptr!= nullptr) {
		//when o hit m, audio is played
		audio_->Play();
		//And its Disabled
		DisableObject();
		if (GetWorldTimerManager().IsTimerActive(timer_)) {
			GetWorldTimerManager().ClearTimer(timer_);
		}
	}
}

void AMObject::OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed) {
	SetClicked(true);
}



