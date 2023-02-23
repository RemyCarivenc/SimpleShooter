// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* playerController = Cast<APlayerController>(PawnKilled->GetController());
    if(playerController != nullptr)
    {
        playerController->GameHasEnded(nullptr,false);
    }
}