// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ChooseNextWayPoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_UE4_API UChooseNextWayPoint : public UBTTaskNode
{
	GENERATED_BODY()

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard Data")
		struct FBlackboardKeySelector IndexKey;

};
