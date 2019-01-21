#pragma once

#include "../FGAbilityBase.h"
#include "Combat/FGBodyParts.h"
#include "FGTakeAim.generated.h"

UCLASS()
class FGFPS_API UFGTakeAim : public UFGAbilityBase
{
	GENERATED_BODY()
public:
	virtual bool Initialize(TWeakObjectPtr<class UWorld> NewWorld, class AFGCharacter* NewCaster) override;

	virtual EFGAbilityUseErrorType HandleAbilityUse(class AFGCharacter* Target) override;

	/** Take Aim specifics. */
	UFUNCTION()
	void OnBodyPartSelected(EFGBodyPart SelectedPart);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widgets)
	TSubclassOf<class UFGBodyPartSelectorWidget> BodyPartSelectWidgetClass;

	UPROPERTY(VisibleAnywhere)
	class UFGBodyPartSelectorWidget* BodyPartSelectWidget = nullptr;

private:
	bool bShouldShowMenu = true;
};
