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
	class ATank* Tank;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 3.f;
	void CheckFireCondition();
	bool InFireRange();
};
