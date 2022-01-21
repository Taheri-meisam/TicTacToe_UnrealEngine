// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnSelector.generated.h"


UCLASS()
class TTT_V01_API APawnSelector : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnSelector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = dots)
	class UMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dots")
		bool bTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dots")
	TArray<UStaticMeshComponent*> Spheres;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dots")
	class UMaterial* RedMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dots")
	class UMaterial* BlueMaterial ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dots")
	class UMaterial* WhiteMaterial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dots")
	TArray<int> PlayerFill;

	//Camera Component 
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;
	// Spring Arm Component 
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* SpringArm;

	UFUNCTION(Category = UFunctions)
	void OnePressed();

	UFUNCTION(Category = UFunctions)
	void TwoPressed();

	UFUNCTION(Category = UFunctions)
	void ThreePressed();

	UFUNCTION(Category = UFunctions)
	void FourPressed();

	UFUNCTION(Category = UFunctions)
	void FivePressed();

	UFUNCTION(Category = UFunctions)
	void SixPressed();

	UFUNCTION(Category = UFunctions)
	void SevenPressed();

	UFUNCTION(Category = UFunctions)
	void EightPressed();

	UFUNCTION(Category = UFunctions)
	void NinePressed();

	UFUNCTION(Category = UFunctions)
	void WinFunction();


	//size of array


};
