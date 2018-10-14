// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "Terrain/ActorPool.h"
#include "EngineUtils.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(TEXT("ActorPool"));


}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*(VolumeIterator));
		++VolumeIterator;
	}

}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	//UE_LOG(LogTemp, Warning, TEXT("Found Volume: %s"), *VolumeToAdd->GetName());

}