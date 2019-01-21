#include "UI/Widgets/FGCombatTextWidget.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Player/FGPlayerCharacter.h"
#include "Components/FGCombatComponent.h"

#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "Lua/FGLuaContext.h"
#include "TextBlock.h"

void UFGCombatTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CombatText = Cast<UTextBlock>(GetWidgetFromName("CombatText"));
}

void UFGCombatTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetLuaContext())
		GetLuaContext()->CallFunction("Update", InDeltaTime);
}

void UFGCombatTextWidget::AddLuaFunctionality(const FString& Filename)
{
	Super::AddLuaFunctionality(Filename);

	luabridge::getGlobalNamespace(GetLuaContext()->GetLuaState())
		.beginClass<UFGCombatTextWidget>("FloatingCombatText")
			.addFunction("UpdatePosition", &UFGCombatTextWidget::UpdatePosition)
			.addFunction("Hide", &UFGCombatTextWidget::Hide)
		.endClass();

	luabridge::push(GetLuaContext()->GetLuaState(), this);
	lua_setglobal(LuaContext->GetLuaState(), "FCT"); // FCT = Floating Combat Text
}

void UFGCombatTextWidget::Display(const FFGCombatTextData& Data)
{
	CurrentData = Data;
	if (CurrentData.DamageType != EFGDamageType::DT_None)
	{
		PlayerController = Data.Player->GetPlayerController();
		if (!PlayerController) { return; }

		FText Text;
		bIsFCTEnabled = true;
		
		if (CurrentData.DamageType == EFGDamageType::DT_Miss)
		{
			Text = FText::FromString("miss");
		}
		else if (CurrentData.DamageType == EFGDamageType::DT_Normal)
		{
			Text = FText::AsNumber(CurrentData.NumberToDisplay);
		}

		CombatText->SetText(Text);
		SetVisibility(ESlateVisibility::Visible);
		SetPositionInViewport(CurrentData.Position);	
	}
	else
	{
		Hide();
	}
}

void UFGCombatTextWidget::Hide()
{
	PlayerController = nullptr;
	CurrentData.Clear();
	bIsFCTEnabled = false;

	SetVisibility(ESlateVisibility::Hidden);
}

void UFGCombatTextWidget::UpdatePosition(float DeltaTime)
{
	FVector2D ActorScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(PlayerController, CurrentData.DockPosition, ActorScreenPosition);

	CurrentData.Position = ActorScreenPosition;

	CurrentData.Offset -= CurrentData.Speed * DeltaTime;
	CurrentData.Position.Y += CurrentData.Offset;

	SetPositionInViewport(CurrentData.Position);
}
