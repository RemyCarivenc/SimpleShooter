// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        APawn *playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);


        GetBlackboardComponent()->SetValueAsVector("StartLocation",GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector("PlayerLocation",playerPawn->GetActorLocation());
    }
   
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* controlledCharacter =  Cast<AShooterCharacter>(GetPawn());
    if(controlledCharacter != nullptr)
    {
        return controlledCharacter->IsDead();
    }

    return true;
}
