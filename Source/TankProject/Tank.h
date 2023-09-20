#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"
#include "Tank.generated.h"


UCLASS()
class TANKPROJECT_API ATank : public ABasicPawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	
	APlayerController* GetPlayerControllerRef() const;

protected:
	virtual void BeginPlay() override;

	void RotateTurret(FVector TargetLocation);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float Speed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float RotateSpeed = 150.f;
	
	UPROPERTY(VisibleAnywhere, category="Camera")
	class USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, category="Camera")
	class UCameraComponent* CameraComp;

	class APlayerController* PlayerControllerRef;

	void Move(float value);

	void Turn(float value);
};
