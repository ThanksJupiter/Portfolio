#pragma once

#include "Combat/FGDamageTypes.h"
#include "UI/FGWidgetBase.h"
#include "FGCombatTextWidget.generated.h"

USTRUCT(BlueprintType)
struct FFGCombatTextData
{
	GENERATED_BODY()

	class AFGPlayerCharacter* Player = nullptr;
	EFGDamageType DamageType = EFGDamageType::DT_None;
	FVector2D Position = FVector2D::ZeroVector;
	float Offset = 0.0f;
	float Speed = 0.0f;
	class AFGCharacter* HitActor = nullptr;
	FVector DockPosition = FVector::ZeroVector;
	float NumberToDisplay = 0;
	float Duration = 0.0f;

	void Clear()
	{
		Player = nullptr;
		DamageType = EFGDamageType::DT_None;
		Position = FVector2D::ZeroVector;
		Offset = 0.0f;
		Speed = 0.0f;
		HitActor = nullptr;
		DockPosition = FVector::ZeroVector;
		NumberToDisplay = 0;
		Duration = 0.0f;
	}
};

UCLASS()
class FGFPS_API UFGCombatTextWidget : public UFGWidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void AddLuaFunctionality(const FString& Filename) override;

	class UTextBlock* CombatText = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	class APlayerController* PlayerController = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	float RemainingTime = 0.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Spawning)
	bool bIsFCTEnabled = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Data")
	FFGCombatTextData CurrentData;

	UFUNCTION(BlueprintCallable)
	void Display(const FFGCombatTextData& Data);

	UFUNCTION(BlueprintCallable)
	void Hide();

	UFUNCTION(BlueprintCallable)
	void UpdatePosition(float DeltaTime);
};
