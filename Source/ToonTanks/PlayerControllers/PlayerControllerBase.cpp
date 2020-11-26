// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnableState(bool SetPlayerEnabled)
{
	SetPlayerEnabled ? GetPawn()->EnableInput(this) : GetPawn()->DisableInput(this);

	bShowMouseCursor = SetPlayerEnabled;
}