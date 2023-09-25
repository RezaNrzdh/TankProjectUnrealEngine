#include "HealthComponent.h"
#include "TankGameModeBase.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(GetOwner() == Tank)
	{
		Tank->GetCurrentHealth(Health/MaxHealth);
	}
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	TankGameModeBase = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;

	Health -= Damage;
	if(DamagedActor == Tank)
	{
		Tank->GetCurrentHealth(Health/MaxHealth);	
	}
	if(Health <= 0.f && TankGameModeBase)
	{
		TankGameModeBase->ActorDied(DamagedActor);
	}
}

float UHealthComponent::TestFunc()
{
	return 717.f;
}


