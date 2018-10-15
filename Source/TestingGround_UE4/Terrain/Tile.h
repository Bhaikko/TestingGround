// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;

};



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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "RandomData")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinNum = 1, int32 MaxNum = 1, float Radius = 700, float MinScale = 1, float MaxScale = 1);
	UFUNCTION(BlueprintCallable, Category = "RandomData")
		void PlaceAIPawns(TSubclassOf<class APawn> ToSpawn, int32 MinNum = 1, int32 MaxNum = 1, float Radius = 700);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PoolReference(UActorPool* PoolToSet);

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& SpawnPoint,float Radius);

	TArray<FSpawnPosition> RandomSpawnPoints(int32 MinNum, int32 MaxNum, float Radius, float MinScale, float MaxScale);

	void SpawnActor(TSubclassOf<AActor> ToSpawn,const FSpawnPosition& SpawnPosition);

	void SpawnAIPawns(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	class UActorPool* Pool;

	AActor* NavMeshVolume;

	void PositionNavmeshVolume();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MaxExtend;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MinExtend;

	
	
};
