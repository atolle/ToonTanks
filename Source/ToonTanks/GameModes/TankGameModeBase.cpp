// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();

}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("A Pawn died, RIP"));

	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		DisablePlayerState();

		return;
	}		

	APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor);

	if (DestroyedTurret)
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets--;
	}
	
	if (TargetTurrets == 0)
		HandleGameOver(true);
}

void ATankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	DisablePlayerState();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}

void ATankGameModeBase::EnablePlayerState()
{
	if (PlayerController)
		PlayerController->SetPlayerEnableState(true);
}

void ATankGameModeBase::DisablePlayerState()
{
	if (PlayerController)
		PlayerController->SetPlayerEnableState(false);
}