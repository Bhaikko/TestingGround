// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUND_UE4_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "RandomData")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinNum = 1, int32 MaxNum = 1, float Radius = 700, float MinScale = 1, float MaxScale = 1);

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& SpawnPoint,float Radius);

	void SpawnActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint,float Rotation,float Scale);
	
};
