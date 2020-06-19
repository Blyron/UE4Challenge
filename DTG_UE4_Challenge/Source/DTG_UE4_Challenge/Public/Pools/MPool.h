// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/MObject.h"
#include "MPool.generated.h"

UCLASS()
class DTG_UE4_CHALLENGE_API AMPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPool();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
		int m_objects_spawned_ = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		TSubclassOf<AMObject> m_object_type_;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Container with the objects
	UPROPERTY()
		TArray<AMObject*> m_objects_;

public:	

	// param position : position in which the object will spawn
	// return a reference to spawned object
	AMObject* SpawnMObject(FVector position);
private:
	int current_array_index_;
};
