// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGround_UE4.h"
#include "TestingGround_UE4GameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_UE4_API AInfiniteTerrainGameMode : public ATestingGround_UE4GameMode
{
	GENERATED_BODY()

public:

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "BoundsPool")
		void PopulateBoundsVolumePool();

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pool")
		class UActorPool* NavMeshBoundsVolumePool;
	
};
