// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}


void ATankGameModeBase::HandleGameStart()
{
	EnemyCount = GetEnemyCount();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();
	
	if(TankPlayerController)
	{
		TankPlayerController->SetPlayerEnableState(false);

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
			TankPlayerController,
			&ATankPlayerController::SetPlayerEnableState,
			true);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, StartDelay, false);
	}
}


void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if(TankPlayerController)
		{
			TankPlayerController->SetPlayerEnableState(false);
		}
		EndGame(false);
	}
	else if(ATower* Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();
		EnemyCount = EnemyCount - 1;
		if(EnemyCount == 0)
		{
			EndGame(true);
		}
	}
}

int32 ATankGameModeBase::GetEnemyCount()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(),Enemies);
	return Enemies.Num();
}