// Copyright 2016 P906, Perfect World, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidgetHead.h"
#include "InputRawDataStructs.h"
#include "StringTableRegistry.h"
#include "WidgetBase.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EBindingTypes : uint8
{
	Menu,
	MenuSpecial,
	Bumpers,
	Triggers,
	LeftStick,
	LeftStickAxes,
	RightStick,
	RightStickAxes,
	TouchPad
};

/** Current state of the check box */
UENUM(BlueprintType)
enum class ECheckState : uint8
{
	None,
	/** Unchecked */
	Unchecked,
	/** Checked */
	Checked,
	/** Neither checked nor unchecked */
	Hovered,

	Undetermined,
};


DECLARE_DELEGATE(FOnClickedEvent);

/**
 *
 */
UCLASS()
class PWGAME_API UPWWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	/************************************************************************/
	/*  �����󶨺���  Action Binding Functions                                */
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Category = "Gamepad")
		virtual void ApplyBindings(UPARAM(meta = (Bitmask, BitmaskEnum = EBindingTypes)) int32 IgnoreBindings = 0, bool bUseRegionalButton = true);

	UFUNCTION(BlueprintCallable, Category = "Gamepad")
		void ResetBindings();

	virtual void BindMenu(bool bUseRegionalButton = true);
	virtual void BindMenuSpecial();
	virtual void BindBumpers();
	virtual void BindTriggers();
	virtual void BindLeftStick();
	virtual void BindLeftStickAxes();
	virtual void BindRightStick();
	virtual void BindRightStickAxes();
	virtual void BindTouchPad();


	/************************************************************************/
	/*  ����ر���  Binding Variables                                       */
	/************************************************************************/

	// GM ��
	UPROPERTY(BlueprintReadWrite, Category = "WidgetBase")
		uint8 bShowPlayerPosition : 1;

	// X ��仯��������ֵ���ӽ������и�ֵ
	UPROPERTY(BlueprintReadWrite, Category = "WidgetBase")
		float XAxis;

	// Y ��仯��������ֵ���ӽ������и�ֵ
	UPROPERTY(BlueprintReadWrite, Category = "WidgetBase")
		float YAxis;



	/************************************************************************/
	/*  ���̺���  Procedure Functions                                        */
	/************************************************************************/

	// WidgetManager ���� Widget ǰ����
	UFUNCTION(BlueprintNativeEvent, Category = "WidgetBase")
		void OnPreHide();
	virtual void OnPreHide_Implementation();

	// WidgetManager ���� Widget ʱ����
	UFUNCTION(BlueprintNativeEvent, Category = "WidgetBase")
		void OnHide();
	virtual void OnHide_Implementation();



	/************************************************************************/
	/*  ���ߺ���  Utensil Functions                                          */
	/************************************************************************/

	/**
	 * ��������ʱ���水��ʱ�������ز������ӵ�����
	 * һ������ Repeat ������������¼���ļ���Ч��
	 * ��������Ϊÿ������1
	 * ���� 1���ڷ���1��1��~2�뷵��2��2��~3�뷵��3
	 *
	 * @param bStickAsArrow �Ƿ����ҡ�˵��� Arrow
	 * @param Limit ��߼��ٵĴ�����������ֵ�����ֵ
	 * @param Scale 2�����٣���Ϊ2����ô0.5���ڷ���1��0.5~1���ڷ���2���Դ����ơ�
	 * @return ���ؼ��ٺ�Ĵ���
	 */
	UFUNCTION(BlueprintCallable, Category = "Gamepad")
		void IncreaseNumByTime(const bool bStickIsArrow, const FKey Key, int32& Time, float& Delay, int32 Limit = 3, int32 Scale = 1);

	void SetWigetID(EUMGID id) { WidgetID = id; }
	EUMGID GetWidgetID() { return WidgetID; }

	void SetWillGetControl(bool value) { WillGetControl = value; }
	bool IsWillGetControl() { return WillGetControl; }



	/************************************************************************/
	/*  ���󶨵ĺ���  Bound Functions                                        */
	/************************************************************************/

	// Menu direction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuUpPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuDownPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuLeftPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuRightPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuUpReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuDownReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuLeftReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuRightReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuUpRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuDownRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuLeftRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuRightRepeat();

	// Menu button
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAcceptPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuCancelPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAcceptReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuCancelReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAcceptRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuCancelRepeat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAction1Pressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAction2Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAction1Released();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAction2Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAction1Repeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuAction2Repeat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuSpecialLeftPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuSpecialRightPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuSpecialLeftReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuSpecialRightReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuSpecialLeftRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void MenuSpecialRightRepeat();

	// Shoulder & Trigger
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void L1Pressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void L2Pressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void R1Pressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void R2Pressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void L1Released();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void L2Released();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void R1Released();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void R2Released();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void L1Repeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void L2Repeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void R1Repeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void R2Repeat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void L2Axis(float val);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void R2Axis(float val);

	// Right Stick
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickUpPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickDownPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickLeftPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickRightPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickUpReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickDownReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickLeftReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickRightReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickUpRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickDownRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickLeftRepeat();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickRightRepeat();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickXAxis(float val);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void RightStickYAxis(float val);

	// Left Stick
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void LeftStickXAxis(float val);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void LeftStickYAxis(float val);

	// Touch Pad
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void TouchPadXAxis(float val);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gamepad")
		void TouchPadYAxis(float val);


	UFUNCTION(BlueprintCallable, Category = "Gamepad")
		void ClearChildenWithOutFirst(UPanelWidget* ParentWidget);

protected:
	UFUNCTION(BlueprintCallable, Category = "WidgetBase")
		void Close();
	/************************************************************************/
	/*  ���󶨵ĺ���  Bound Functions                                        */
	/************************************************************************/

	virtual void SetupInputComponent();

	// Menu direction
	virtual void MenuUpPressed_Implementation() { }
	virtual void MenuDownPressed_Implementation() { }
	virtual void MenuLeftPressed_Implementation() { }
	virtual void MenuRightPressed_Implementation() { }

	virtual void MenuUpReleased_Implementation() { }
	virtual void MenuDownReleased_Implementation() { }
	virtual void MenuLeftReleased_Implementation() { }
	virtual void MenuRightReleased_Implementation() { }

	virtual void MenuUpRepeat_Implementation() { }
	virtual void MenuDownRepeat_Implementation() { }
	virtual void MenuLeftRepeat_Implementation() { }
	virtual void MenuRightRepeat_Implementation() { }


	// Menu button
	virtual void MenuAcceptPressed_Implementation() { }
	virtual void MenuCancelPressed_Implementation() { }

	virtual void MenuAcceptReleased_Implementation() { }
	virtual void MenuCancelReleased_Implementation() { }

	virtual void MenuAcceptRepeat_Implementation() { }
	virtual void MenuCancelRepeat_Implementation() { }

	virtual void MenuAction1Pressed_Implementation() { }
	virtual void MenuAction2Pressed_Implementation() { }

	virtual void MenuAction1Released_Implementation() { }
	virtual void MenuAction2Released_Implementation() { }

	virtual void MenuAction1Repeat_Implementation() { }
	virtual void MenuAction2Repeat_Implementation() { }

	virtual void MenuSpecialLeftPressed_Implementation() { }
	virtual void MenuSpecialRightPressed_Implementation() { }

	virtual void MenuSpecialLeftReleased_Implementation() { }
	virtual void MenuSpecialRightReleased_Implementation() { }

	virtual void MenuSpecialLeftRepeat_Implementation() { }
	virtual void MenuSpecialRightRepeat_Implementation() { }

	// Shoulder & Trigger
	virtual void L1Pressed_Implementation() { }
	virtual void L2Pressed_Implementation() { }
	virtual void R1Pressed_Implementation() { }
	virtual void R2Pressed_Implementation() { }

	virtual void L1Released_Implementation() { }
	virtual void L2Released_Implementation() { }
	virtual void R1Released_Implementation() { }
	virtual void R2Released_Implementation() { }

	virtual void L1Repeat_Implementation() { }
	virtual void L2Repeat_Implementation() { }
	virtual void R1Repeat_Implementation() { }
	virtual void R2Repeat_Implementation() { }


	virtual void L2Axis_Implementation(float val) { }
	virtual void R2Axis_Implementation(float val) { }

	// Right Stick
	virtual void RightStickUpPressed_Implementation() { }
	virtual void RightStickDownPressed_Implementation() { }
	virtual void RightStickLeftPressed_Implementation() { }
	virtual void RightStickRightPressed_Implementation() { }

	virtual void RightStickUpReleased_Implementation() { }
	virtual void RightStickDownReleased_Implementation() { }
	virtual void RightStickLeftReleased_Implementation() { }
	virtual void RightStickRightReleased_Implementation() { }

	virtual void RightStickUpRepeat_Implementation() { }
	virtual void RightStickDownRepeat_Implementation() { }
	virtual void RightStickLeftRepeat_Implementation() { }
	virtual void RightStickRightRepeat_Implementation() { }

	virtual void RightStickXAxis_Implementation(float val) { }
	virtual void RightStickYAxis_Implementation(float val) { }

	// Left Stick
	virtual void LeftStickXAxis_Implementation(float val) { }
	virtual void LeftStickYAxis_Implementation(float val) { }

	// Touch Pad
	virtual void TouchPadXAxis_Implementation(float val) { }
	virtual void TouchPadYAxis_Implementation(float val) { }

	UFUNCTION(BlueprintCallable, Category = "MouseEvent")
		virtual	void OnMouseEnterEvent(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {}

	UFUNCTION(BlueprintCallable, Category = "MouseEvent")
		virtual	void OnMouseLeaveEvent(const FPointerEvent& InMouseEvent) {}

	UFUNCTION(BlueprintCallable, Category = "MouseEvent")
		virtual FEventReply OnMouseButtonDownEvent(const FGeometry& OnMouseButtonDown, const FPointerEvent& InMouseEvent)
	{
		FEventReply Reply(false);
		return Reply;
	}


protected:
	EUMGID		WidgetID;
	bool		WillGetControl;
};
