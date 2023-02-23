// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr)
        return EBTNodeResult::Failed;

    AShooterCharacter* character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(character == nullptr)
        return EBTNodeResult::Failed;

    character->Shoot();

    return EBTNodeResult::Succeeded;
}