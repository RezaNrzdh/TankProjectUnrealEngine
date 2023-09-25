#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
    CameraComp->SetupAttachment(SpringArmComp);
}


void ATank::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerControllerRef = Cast<APlayerController>(GetController());
}


void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.0f);
    }
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}




void ATank::Move(float value)
{   
    FVector offset = FVector(0,0,0);
    offset.X = value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(offset, true);
}


void ATank::Turn(float value)
{
    FRotator Rotate = FRotator(0,0,0);
    Rotate.Yaw = value * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(Rotate);
}



void ATank::RotateTurret(FVector TargetLocation)
{
    FVector TargetTo = TurretMesh->GetComponentLocation() - TargetLocation;
    FRotator LookAtRotation = FRotator(0.f, TargetTo.Rotation().Yaw + 90.f, 0.f);
    TurretMesh->SetWorldRotation(FMath::RInterpTo(
        TurretMesh->GetComponentRotation(),
        LookAtRotation,
        UGameplayStatics::GetWorldDeltaSeconds(this),
        8.f)
        );
}



void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    
    UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

    bTankAlive = false;
}



APlayerController* ATank::GetPlayerControllerRef() const
{
    return PlayerControllerRef;
}



void ATank::GetCurrentHealth(float Health)
{
    CurrentHealthVar = Health;
}



float ATank::CurrentHealth()
{
    return CurrentHealthVar;
}



bool ATank::GetTankAlive()
{
    return bTankAlive;
}


void ATank::Fire()
{
    Super::Fire();
}


