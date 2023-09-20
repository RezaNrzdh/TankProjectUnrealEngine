#include "Tower.h"

#include "Projectile.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"



ATower::ATower()
{
	
}



void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}



void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(InFireRange())
	{
		FVector  TargetTo = TurretMesh->GetComponentLocation() - Tank->GetActorLocation();
		FRotator LookAtRotation = FRotator(0.f, TargetTo.Rotation().Yaw + 90.f,0.f);
		TurretMesh->SetWorldRotation(FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f)
			);
	}
}



bool ATower::InFireRange()
{
	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(Distance <= 4000.f)
		{
			return true;
		}
	}
	return false;
}



void ATower::CheckFireCondition()
{
	if(InFireRange())
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
	Destroy();
}