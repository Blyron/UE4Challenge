// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "MObject.generated.h"

//This is the marble class
//It has audio component for feedback
//Settings parameters can be edited from BP to adjust them 
//depending on gameplay

UCLASS()
class DTG_UE4_CHALLENGE_API AMObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* mesh_;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UAudioComponent* audio_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
		float time_until_dissapear_post_iteraction_ = 5.0f;
	//constant force intensity for when you drag the marble
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float force_intensity_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void ActiveObject(bool active);
	UFUNCTION()
		void DisableObject();
	//Add force to the marble in XY plane
	UFUNCTION()
		void AddForce(FVector forceToAdd);
	UFUNCTION(BlueprintGetter)
		bool active();
	UFUNCTION(BlueprintSetter)
		void SetClicked(bool clicked);
	UFUNCTION(BlueprintGetter)
		bool clicked();
private:
	bool active_;
	bool clicked_;
	//Timer used to disable the object after interaction
	FTimerHandle timer_;
	//Hit function for feedback and disable in case of hitting the target
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	//Function to know if the start has start on this object.
	UFUNCTION()
		void OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);


};
