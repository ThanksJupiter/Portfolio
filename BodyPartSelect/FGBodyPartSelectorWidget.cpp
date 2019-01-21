#include "FGBodyPartSelectorWidget.h"
#include "UI/Button/FGButton.h"
#include "WidgetTree.h"
#include "CanvasPanel.h"
#include "Loot/Items/FGItem.h"

void UFGBodyPartSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Canvas = Cast<UCanvasPanel>(GetWidgetFromName("CanvasPanel_0"));

 	HeadBTN = Cast<UFGButton>(GetWidgetFromName("Head_BTN"));
 	HeadBTN->OnButtonClicked.AddDynamic(this, &UFGBodyPartSelectorWidget::HandleButtonClicked);
 
 	TorsoBTN = Cast<UFGButton>(GetWidgetFromName("Torso_BTN"));
 	TorsoBTN->OnButtonClicked.AddDynamic(this, &UFGBodyPartSelectorWidget::HandleButtonClicked);
 
 	LeftElbowBTN = Cast<UFGButton>(GetWidgetFromName("Arm_l_BTN"));
 	LeftElbowBTN->OnButtonClicked.AddDynamic(this, &UFGBodyPartSelectorWidget::HandleButtonClicked);
 
 	RightElbowBTN = Cast<UFGButton>(GetWidgetFromName("Arm_r_BTN"));
 	RightElbowBTN->OnButtonClicked.AddDynamic(this, &UFGBodyPartSelectorWidget::HandleButtonClicked);
 
 	LeftKneeBTN = Cast<UFGButton>(GetWidgetFromName("Leg_l_BTN"));
 	LeftKneeBTN->OnButtonClicked.AddDynamic(this, &UFGBodyPartSelectorWidget::HandleButtonClicked);
 
 	RightKneeBTN = Cast<UFGButton>(GetWidgetFromName("Leg_r_BTN"));
 	RightKneeBTN->OnButtonClicked.AddDynamic(this, &UFGBodyPartSelectorWidget::HandleButtonClicked);
}

void UFGBodyPartSelectorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UFGBodyPartSelectorWidget::Display()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UFGBodyPartSelectorWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UFGBodyPartSelectorWidget::HandleButtonClicked(UFGButton* ClickedButton)
{
	if (!ClickedButton->ItemToPickup)
		HandleSelectBodyPart(ClickedButton->SelectBodyPart);
}

void UFGBodyPartSelectorWidget::HandleSelectBodyPart(EFGBodyPart SelectedPart)
{
	OnPartSelected.Broadcast(SelectedPart);
}

void UFGBodyPartSelectorWidget::HandleItemClicked(UFGItem* SelectedItem)
{
	OnItemSelected.Broadcast(SelectedItem);
}
