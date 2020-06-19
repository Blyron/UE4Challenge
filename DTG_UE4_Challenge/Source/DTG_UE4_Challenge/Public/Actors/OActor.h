// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/MObject.h"
#include "OActor.generated.h"

//This is the o class which is the target to hit.
UCLASS()
class DTG_UE4_CHALLENGE_API AOActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* mesh_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
