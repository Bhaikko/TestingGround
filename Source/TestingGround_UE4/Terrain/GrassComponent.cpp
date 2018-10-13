// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"

void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnGrass();

}


void UGrassComponent::SpawnGrass()
{
	for (int i = 1; i <= SpawnCount; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(SpawningExtents);
		AddInstance(FTransform(SpawnLocation));
	}
	//UE_LOG(LogTemp, Warning, TEXT("GrassSpawned"));
	return;
}



