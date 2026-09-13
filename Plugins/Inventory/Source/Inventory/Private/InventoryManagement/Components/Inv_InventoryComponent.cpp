// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"

UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	ConstructInventory();
}

void UInv_InventoryComponent::ConstructInventory()
{
	OwningPlayerController = Cast<APlayerController>(GetOwner());
	checkf(OwningPlayerController.IsValid(), TEXT("Inventory Component should have a Player Controller as owner."))
	if (!OwningPlayerController->IsLocalController()) return;
	
	InventoryMenu = CreateWidget<UInv_InventoryBase>(OwningPlayerController.Get(), InventoryMenuClass);
	InventoryMenu->AddToViewport();
	CloseInventoryMenu();
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	bInventoryMenuOpen ? CloseInventoryMenu() : OpenInventoryMenu();
}

void UInv_InventoryComponent::OpenInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	InventoryMenu->SetVisibility(ESlateVisibility::Visible);
	bInventoryMenuOpen = true;
	
	if (!OwningPlayerController.IsValid()) return;
	FInputModeGameAndUI InputMode;
	OwningPlayerController->SetInputMode(InputMode);
	OwningPlayerController->SetShowMouseCursor(true);
}

void UInv_InventoryComponent::CloseInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
	bInventoryMenuOpen = false;
	
	if (!OwningPlayerController.IsValid()) return;
	FInputModeGameOnly InputMode;
	OwningPlayerController->SetInputMode(InputMode);
	OwningPlayerController->SetShowMouseCursor(false);
}
