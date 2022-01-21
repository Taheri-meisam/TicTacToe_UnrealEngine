// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnSelector.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <UObject/ConstructorHelpers.h>
#include "Containers/Array.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Misc/Char.h"
#include "Misc/MessageDialog.h"
#include "Math/UnrealMathUtility.h"
// Sets default values

#define LOCTEXT_NAMESPACE "MyOtherNamespace"  
APawnSelector::APawnSelector()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	Spheres.Init(NULL, 9);
	PlayerFill.Init(0, 9);
	bTurn = true;
	Spheres[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres1Component"));
	Spheres[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres2Component"));
	Spheres[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres3omponent"));
	Spheres[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres4Component"));
	Spheres[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres5Component"));
	Spheres[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres6Component"));
	Spheres[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres7Component"));
	Spheres[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres8Component"));
	Spheres[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spheres9Component"));
	//Spheres[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpheresComponent"));

	RedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	BlueMaterial = CreateDefaultSubobject<UMaterial>(TEXT("BlueMaterial"));

	//spring arm 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f)); // rotate the camera to look down 
	SpringArm->TargetArmLength = 500.f; // lenght of the boom
	// these are good for when you move the pawn and colid with something 
	SpringArm->bEnableCameraLag = true; 
	SpringArm->CameraLagSpeed = 3.f;
	//camera 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	//Spheres[0]->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	int ArraySize = Spheres.Num();
	if (MeshComponentAsset.Succeeded()) {
		for (int i = 0; i < ArraySize; i++) {
			Spheres[i]->SetStaticMesh(MeshComponentAsset.Object);
			Spheres[i]->SetMaterial(0, WhiteMaterial);
		}
	}

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APawnSelector::BeginPlay()
{
	Super::BeginPlay();
	//this is sample if you want to add AI to your Game. How to generate random numbers 
	int RandVal = FMath::RandRange(0, 100);
	UE_LOG(LogTemp, Warning, TEXT("Player 2 input%s"), *FString::FromInt(RandVal));
	//
	// set the location of each Sphere 
	MeshComponent->SetWorldLocation(FVector(-600.f, 900.f, 500.f));
	Spheres[0]->SetWorldLocation(FVector(0.f, 100.f, 100.f));
	Spheres[1]->SetWorldLocation(FVector(0.f, 300.f, 100.f));
	Spheres[2]->SetWorldLocation(FVector(0.f, 500.f, 100.f));
	Spheres[3]->SetWorldLocation(FVector(-200.f, 100.f, 100.f));
	Spheres[4]->SetWorldLocation(FVector(-200.f, 300.f, 100.f));
	Spheres[5]->SetWorldLocation(FVector(-200.f, 500.f, 100.f));
	Spheres[6]->SetWorldLocation(FVector(-400.f, 100.f, 100.f));
	Spheres[7]->SetWorldLocation(FVector(-400.f, 300.f, 100.f));
	Spheres[8]->SetWorldLocation(FVector(-400.f, 500.f, 100.f));
	
}

// Called every frame
void APawnSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void APawnSelector::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("One", IE_Pressed, this, &APawnSelector::OnePressed);
	InputComponent->BindAction("two", IE_Pressed, this, &APawnSelector::TwoPressed);
	InputComponent->BindAction("three", IE_Pressed, this, &APawnSelector::ThreePressed);
	InputComponent->BindAction("four", IE_Pressed, this, &APawnSelector::FourPressed);
	InputComponent->BindAction("five", IE_Pressed, this, &APawnSelector::FivePressed);
	InputComponent->BindAction("six", IE_Pressed, this, &APawnSelector::SixPressed);
	InputComponent->BindAction("seven", IE_Pressed, this, &APawnSelector::SevenPressed);
	InputComponent->BindAction("eight", IE_Pressed, this, &APawnSelector::EightPressed);
	InputComponent->BindAction("nine", IE_Pressed, this, &APawnSelector::NinePressed);
	//You can use  IE_Released to trigger a function to do something when you release the Key
	//InputComponent->BindAction("nine", IE_Released , this, &APawnSelector::NinePressed);

}

void APawnSelector::OnePressed()
{
	
	if (bTurn == true && PlayerFill[0] == 0) {
		Spheres[0]->SetMaterial(0, BlueMaterial);
		PlayerFill[0] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));	
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[0] == 0){
		Spheres[0]->SetMaterial(0, RedMaterial);
		PlayerFill[0] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}

}

void APawnSelector::TwoPressed()
{
	if (bTurn == true && PlayerFill[1] == 0) {
		Spheres[1]->SetMaterial(0, BlueMaterial);
		PlayerFill[1] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[1] == 0) {
		Spheres[1]->SetMaterial(0, RedMaterial);
		PlayerFill[1] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}


}

void APawnSelector::ThreePressed()
{
	if (bTurn == true && PlayerFill[2] == 0) {
		Spheres[2]->SetMaterial(0, BlueMaterial);
		PlayerFill[2] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[2] == 0) {
		Spheres[2]->SetMaterial(0, RedMaterial);
		PlayerFill[2] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}
}

void APawnSelector::FourPressed()
{
	if (bTurn == true && PlayerFill[3] == 0) {
		Spheres[3]->SetMaterial(0, BlueMaterial);
		PlayerFill[3] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[3] == 0) {
		Spheres[3]->SetMaterial(0, RedMaterial);
		PlayerFill[3] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}
}

void APawnSelector::FivePressed()
{
	if (bTurn == true && PlayerFill[4] == 0) {
		Spheres[4]->SetMaterial(0, BlueMaterial);
		PlayerFill[4] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[4] == 0) {
		Spheres[4]->SetMaterial(0, RedMaterial);
		PlayerFill[4] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}
}

void APawnSelector::SixPressed()
{
	if (bTurn == true && PlayerFill[5] == 0) {
		Spheres[5]->SetMaterial(0, BlueMaterial);
		PlayerFill[5] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[5] == 0) {
		Spheres[5]->SetMaterial(0, RedMaterial);
		PlayerFill[5] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}
}

void APawnSelector::SevenPressed()
{
	if (bTurn == true && PlayerFill[6] == 0) {
		Spheres[6]->SetMaterial(0, BlueMaterial);
		PlayerFill[6] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[6] == 0) {
		Spheres[6]->SetMaterial(0, RedMaterial);
		PlayerFill[6] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}
}

void APawnSelector::EightPressed()
{
	if (bTurn == true && PlayerFill[7] == 0) {
		Spheres[7]->SetMaterial(0, BlueMaterial);
		PlayerFill[7] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[7] == 0) {
		Spheres[7]->SetMaterial(0, RedMaterial);
		PlayerFill[7] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}
}

void APawnSelector::NinePressed()
{
	if (bTurn == true && PlayerFill[8] == 0) {
		Spheres[8]->SetMaterial(0, BlueMaterial);
		PlayerFill[8] = 1;
		bTurn = false;
		UE_LOG(LogTemp, Warning, TEXT("Player 1 input"));
		WinFunction();
	}
	else if (bTurn == false && PlayerFill[8] == 0) {
		Spheres[8]->SetMaterial(0, RedMaterial);
		PlayerFill[8] = 2;
		bTurn = true;
		UE_LOG(LogTemp, Warning, TEXT("Player 2 input"));
		WinFunction();
	}
}


void APawnSelector::WinFunction()
{
	// Horizental player 1
	if ((PlayerFill[0] == 1 && PlayerFill[1] == 1 && PlayerFill[2] == 1) || 
		(PlayerFill[3] == 1 && PlayerFill[4] == 1 && PlayerFill[5] == 1)|| 
		(PlayerFill[6] == 1 && PlayerFill[7] == 1 && PlayerFill[8] == 1)) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player 1 (Blue Player) win "));
		}
		UE_LOG(LogTemp, Warning, TEXT(" Player 1 win "));
	}

	// horizental player 2
	if ((PlayerFill[0] == 2 && PlayerFill[1] == 2 && PlayerFill[2] == 2) ||
		(PlayerFill[3] == 2 && PlayerFill[4] == 2 && PlayerFill[5] == 2) ||
		(PlayerFill[6] == 2 && PlayerFill[7] == 2 && PlayerFill[8] == 2)) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player 2 (Red Player )win "));
		}
		UE_LOG(LogTemp, Warning, TEXT(" Player 2 win "));
	}


	//Diagnal player 1
	if ((PlayerFill[0] == 1 && PlayerFill[4] == 1 && PlayerFill[8] == 1) ||
		(PlayerFill[2] == 1 && PlayerFill[4] == 1 && PlayerFill[6] == 1) ) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player 1 (Blue Player) win "));
		}
		UE_LOG(LogTemp, Warning, TEXT(" Player 1 win "));
	}



	//Diagnal player 2
	if ((PlayerFill[0] == 2 && PlayerFill[4] == 2 && PlayerFill[8] == 2) ||
		(PlayerFill[2] == 2 && PlayerFill[4] == 2 && PlayerFill[6] == 2)) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player 2 (Red Player) win "));
		}
		UE_LOG(LogTemp, Warning, TEXT(" Player 2 win "));
	}

	// Vertical player 1
	if ((PlayerFill[0] == 1 && PlayerFill[3] == 1 && PlayerFill[6] == 1) ||
		(PlayerFill[1] == 1 && PlayerFill[4] == 1 && PlayerFill[7] == 1) ||
		(PlayerFill[2] == 1 && PlayerFill[5] == 1 && PlayerFill[8] == 1)) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player 1 (Blue Player) win "));
		}
		UE_LOG(LogTemp, Warning, TEXT(" Player 1 win "));
	}



	// Vertical player 2
	if ((PlayerFill[0] == 2 && PlayerFill[3] == 2 && PlayerFill[6] == 2) ||
		(PlayerFill[1] == 2 && PlayerFill[4] == 2 && PlayerFill[7] == 2) ||
		(PlayerFill[2] == 2 && PlayerFill[5] == 2 && PlayerFill[8] == 2)) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player 2 (Red Player) win "));
		}
		UE_LOG(LogTemp, Warning, TEXT(" Player 2 win "));
	}



	//FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT(LOCTEXT_NAMESPACE, "Player 1 win "));
	

	

}
