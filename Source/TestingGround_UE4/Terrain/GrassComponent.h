// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_UE4_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FBox SpawningExtents;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		int32 SpawnCount;

protected:
	virtual void BeginPlay() override;

private:
	void SpawnGrass();

	
	
	
};
