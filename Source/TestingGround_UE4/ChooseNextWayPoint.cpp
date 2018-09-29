
// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i "),Index);
	return EBTNodeResult::Succeeded;
 }

