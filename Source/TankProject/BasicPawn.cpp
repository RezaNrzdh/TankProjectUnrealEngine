// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPawn.h"

#include "NiagaraFunctionLibrary.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


ABasicPawn::ABasicPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(CapsuleComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}



void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void ABasicPawn::HandleDestruction()
{
	//Visual/Sound Effects
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DestrcutionEffect, GetActorLocation(), GetActorRotation());
}



void ABasicPawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	//DrawDebugSphere(GetWorld(), Location, 50.f, 12.f, FColor::Red, false, 3.f);

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjecstileClass, Location, Rotation);
	Projectile->SetOwner(this);

	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
}
