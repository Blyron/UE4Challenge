// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pools/MPool.h"
#include "Actors/OActor.h"
#include "ControllerPawn.generated.h"

//This class is working such as a manager, everything will be spawn from here
//This class will be used to recieve input for spawning M object
//With Space bar we will be able to spawn the marbles.
//Click on marble and drag to flick them
UCLASS()
class DTG_UE4_CHALLENGE_API AControllerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AControllerPawn();
	//Subclasses to spawn the need actos
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		TSubclassOf<AMPool> pool_type_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		TSubclassOf<AOActor> o_type_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//references to the spawned actors
	UPROPERTY()
		AMPool* pool_reference_;	
	//This actor could have been placed on world from editor
	//instead of spawning by code
	UPROPERTY()
		AOActor* o_reference_;

public:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void SpawnNewMObject();
	void MouseClicked();
	void MouseRelease();
	//Position of the mouse when it is clicked
	FVector mouse_src_ps;
	//Position of the mouse when it is released
	FVector mouse_dst_ps;
	//Pointer to the player controller for enabling mouse events
	//and get mouse information
	APlayerController * controller_;
	//reference to the spawned marble
	AMObject* current_m_object_;

	//Control variables
	//If mouse is not valid those vars will be false.
	bool clickresult = false;
	bool releaseresult = false;
	
};
