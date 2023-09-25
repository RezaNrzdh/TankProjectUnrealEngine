#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"
#include "Tower.generated.h"

UCLASS()
class TANKPROJECT_API ATower : public ABasicPawn
{
	GENERATED_BODY()

public:
	ATower();
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
	
protected:
	virtual void BeginPlay() override;

private:
	void CheckFireCondition();
	bool InFireRange();
	bool CheckSweeping();

public:
	UPROPERTY(EditAnywhere)
	float FireRate = 1.f;

protected:

private:
	UPROPERTY(EditAnywhere)
	class USoundBase* ExplosionSound;
	
	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;
	float ShapeRadiusSize = 10.f;
	float MaxDistance = 4000.f;
	bool canWeSeeTank = false;
};
