// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TANKPROJECT_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void EndGame(bool bWonState);
	
private:
	class ATank* Tank;
	class ATankPlayerController* TankPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 EnemyCount = 0;
	int32 GetEnemyCount();

	UPROPERTY(EditAnywhere)
	class USoundBase* BattleSound;
};
