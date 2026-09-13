// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

class UInv_InventoryComponent;
class UInv_HUDWidget;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController {
	GENERATED_BODY()
	
public:
	AInv_PlayerController();
	
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void ToggleInventoryMenu();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	
private:
	void CreateHUDWidget();
	void TraceForItem();
	
	void PrimaryInteract();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> ToggleInventoryAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UInv_HUDWidget> HUDWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	double TraceLength;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;
	
	
	// UPROPERTY prevents a variable from being garbage collected.
	// TWeakObjectPtr does not affect GC status
	TWeakObjectPtr<AActor> HitActor;
	TWeakObjectPtr<AActor> LastHitActor;
	
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
};
