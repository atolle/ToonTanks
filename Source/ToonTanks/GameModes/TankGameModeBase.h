// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	APawnTank* PlayerTank;
	int32 TargetTurrets = 0;
	APlayerControllerBase* PlayerController;

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	int32 GetTargetTurretCount();

public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 3;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	UFUNCTION(BlueprintCallable, Category = "Game Loop")
	void EnablePlayerState();
	UFUNCTION(BlueprintCallable, Category = "Game Loop")
	void DisablePlayerState();
	
};
