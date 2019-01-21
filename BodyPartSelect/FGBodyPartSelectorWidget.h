#pragma once

#include "UI/FGWidgetBase.h"
#include "Combat/FGBodyParts.h"
#include "FGBodyPartSelectorWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGOnPartSelectedSignature, EFGBodyPart, SelectedPart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGOnItemPickupSignature, UFGItem*, SelectedItem);

class UFGButton;

UCLASS()
class FGFPS_API UFGBodyPartSelectorWidget : public UFGWidgetBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void Display();

	UFUNCTION()
	void Hide();

	UFGButton* HeadBTN = nullptr;
	UFGButton* TorsoBTN = nullptr;
	UFGButton* LeftElbowBTN = nullptr;
	UFGButton* RightElbowBTN = nullptr;
	UFGButton* LeftKneeBTN = nullptr;
	UFGButton* RightKneeBTN = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCanvasPanel* Canvas = nullptr;

	FFGOnPartSelectedSignature OnPartSelected;

	FFGOnItemPickupSignature OnItemSelected;

private:
	UFUNCTION()
	void HandleButtonClicked(UFGButton* ClickedButton);

	UFUNCTION()
	void HandleSelectBodyPart(EFGBodyPart SelectedPart);

	UFUNCTION()
	void HandleItemClicked(class UFGItem* SelectedItem);

	template<typename TEnum>
	static FORCEINLINE FString GetENumValueAsString(const FString& Name, TEnum Value)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
		{
			return FString("Invalid");
		}
		return enumPtr->GetNameByValue((int64)Value).ToString();
	}
};
