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
		canWeSeeTank = true;
		FVector  TargetTo = TurretMesh->GetComponentLocation() - Tank->GetActorLocation();
		FRotator LookAtRotation = FRotator(0.f, TargetTo.Rotation().Yaw + 180.f,0.f);
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
		if(Distance <= MaxDistance)
		{
			return true;
		}
	}
	return false;
}



void ATower::CheckFireCondition()
{
	if(InFireRange() && Tank->GetTankAlive() && CheckSweeping())
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	Destroy();
}

bool ATower::CheckSweeping()
{
	FVector Start = GetActorLocation();
	FVector forward  = TurretMesh->GetComponentLocation();
	FVector End   = Start + TurretMesh->GetForwardVector() * MaxDistance;

	FHitResult HitResult;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(ShapeRadiusSize);
	bool isHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, CollisionShape);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2);
	
	if(isHit && HitResult.GetActor() == Tank)
	{
		//UE_LOG(LogTemp, Display, TEXT("%s"), *HitResult.GetActor()->GetActorNameOrLabel());
		return true;
	}
	return false;
}
