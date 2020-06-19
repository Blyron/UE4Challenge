// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/OActor.h"

// Sets default values
AOActor::AOActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh_;
}

// Called when the game starts or when spawned
void AOActor::BeginPlay()
{
	Super::BeginPlay();
	//Enable collisions and physics for hitting
	SetActorEnableCollision(true);
	Cast<UPrimitiveComponent>(RootComponent)->SetSimulatePhysics(true);
}

