#include "FGTakeAim.h"
#include "Character/FGCharacter.h"
#include "Components/FGCombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Lua/FGLuaContext.h"
#include "UI/Widgets/FGBodyPartSelectorWidget.h"
#include "Engine/World.h"

bool UFGTakeAim::Initialize(TWeakObjectPtr<UWorld> NewWorld, class AFGCharacter* NewCaster)
{
	bool Success = Super::Initialize(NewWorld, NewCaster);

	if (BodyPartSelectWidgetClass)
	{
		BodyPartSelectWidget = CreateWidget<UFGBodyPartSelectorWidget>(World->GetWorld(), BodyPartSelectWidgetClass);
		if (BodyPartSelectWidget)
		{
			BodyPartSelectWidget->AddToViewport();
			BodyPartSelectWidget->Hide();
		}
	}

	bShouldShowMenu = true;
	return Success;
}

EFGAbilityUseErrorType UFGTakeAim::HandleAbilityUse(class AFGCharacter* Target)
{
	if (bShouldShowMenu)
	{
		bShouldShowMenu = false;
		OnAbilityUsed.Broadcast(this);
		BodyPartSelectWidget->Display();
		BodyPartSelectWidget->OnPartSelected.AddDynamic(this, &UFGTakeAim::OnBodyPartSelected);

		UGameplayStatics::SetGlobalTimeDilation(World->GetWorld(), GetLuaContext()->GetNumber("TimeDilation"));
	}

	return EFGAbilityUseErrorType::ET_None;
}

void UFGTakeAim::OnBodyPartSelected(EFGBodyPart SelectedPart)
{
	bShouldShowMenu = true;
	Caster->CombatComp->CurrentBodyPartTarget = SelectedPart;
	UGameplayStatics::SetGlobalTimeDilation(World->GetWorld(), 1);
	BodyPartSelectWidget->Hide();
	BodyPartSelectWidget->OnPartSelected.Clear();
}
