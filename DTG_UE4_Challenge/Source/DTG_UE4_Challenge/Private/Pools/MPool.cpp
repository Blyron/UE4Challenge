// Fill out your copyright notice in the Description page of Project Settings.


#include "Pools/MPool.h"

// Sets default values
AMPool::AMPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMPool::BeginPlay()
{
	Super::BeginPlay();
	if (m_object_type_== nullptr)
		return;

	for (int i = 0; i < m_objects_spawned_; ++i) {
		AMObject* object = nullptr;
		object = GetWorld()->SpawnActor<AMObject>(m_object_type_, FTransform::Identity);
		if (object != nullptr)
			m_objects_.Add(object);

	}
	
}



AMObject* AMPool::SpawnMObject(FVector position)
{
	if (m_objects_.Num() < 2)
		return nullptr;

	m_objects_[current_array_index_]->ActiveObject(false);
	current_array_index_++;
	if (current_array_index_ >= m_objects_.Num())
		current_array_index_ = 0;
	m_objects_[current_array_index_]->ActiveObject(true);
	m_objects_[current_array_index_]->SetActorLocation(position);
	return m_objects_[current_array_index_];
}

