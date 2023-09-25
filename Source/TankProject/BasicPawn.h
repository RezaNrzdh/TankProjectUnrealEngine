// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasicPawn.generated.h"

UCLASS()
class TANKPROJECT_API ABasicPawn : public APawn
{
	GENERATED_BODY()

public:
	ABasicPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 myInt = 17;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, category="Projectile")
	TSubclassOf<class AProjectile> ProjecstileClass;

	void Fire();

	void HandleDestruction();

protected:
	UPROPERTY(VisibleAnywhere, category="Component")
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, category="Component")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, category="Component")
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, category="Component")
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* DestrcutionEffect;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;
};
