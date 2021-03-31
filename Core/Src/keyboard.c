#include "keyboard.h"
/////////////////////////////////////////////////////////////////////////////
int Is_Array_NULL(uint8_t Array[]){
	for (uint8_t i = 1; i<=7; i++){
		if (Array[i] !=0) return 0;
	}
	return 1;	
};
//////////////////////////////////////////////////////////////////////////////
void Clone_Array(uint8_t Array1[], uint8_t Array2[]){
		for (int i = 1;i<=7;i++){
			Array2[i] = Array1[i];
		}
};
//////////////////////////////////////////////////////////////////////////////
int Array_Compare(uint8_t Array1[], uint8_t Array2[]){
	for (int i = 0;i<=7;i++){
		if (Array1[i]!=Array2[i]) return 0;
	}
	return 1;
};
//////////////////////////////////////////////////////////////////////////////
void Update_Counters(void){
	Cols_Counters[Col_Number]++;
	Rows_Counters[Row_Number]++;
	Key_State[Row_Number][Col_Number]++;
};
//////////////////////////////////////////////////////////////////////////////
void Clearing_Flags(void){
	*Keys_Counter_Ptr = 3;
	for (uint8_t i  = 1; i<=7; i++){
		USB_Keyboard_Buffer[i] = 0;
	}	
	for (uint8_t i = 0; i<=4; i++){
			Rows_Counters[i] = 0;
			Cols_Counters[i] = 0;
		for (uint8_t j = 0; j<=4; j++){
				Key_State[i][j] = 0;
		}
	}
};
//////////////////////////////////////////////////////////////////////////////
void USB_Data_Usual_Keys_Update (void){
		USB_Keyboard_Buffer[*Keys_Counter_Ptr] = Keys_ID[Col_Number][Row_Number];
		*Keys_Counter_Ptr = *Keys_Counter_Ptr + 1;
		Update_Counters();
};
/////////////////////////////////////////////////////////////////////////////
void USB_Data_Modifier_Keys_Update(void){
		USB_Keyboard_Buffer[1] |= Modifier_Keys_Mask[Row_Number];
		Update_Counters();
};
//////////////////////////////////////////////////////////////////////////////
int Is_Usual_Key_In_HID_Keyboard_Buffer(void){
		for (int i = 2;i <= 7; i++){
			if ((USB_Keyboard_Buffer[i]) == (Keys_ID[Col_Number][Row_Number])) return 0;
		}
		return 1;
};
/////////////////////////////////////////////////////////////////////////////
int Is_Usual_Key_In_HID_Keyboard_Buffer_Old(void){
		for (int i = 2;i <= 7; i++){
			if ((USB_Keyboard_Buffer_Old[i]) == (Keys_ID[Col_Number][Row_Number])) return 1;
		}
		return 0;
};
/////////////////////////////////////////////////////////////////////////////
int Is_Modifier_Key_In_HID_Keyboard_Buffer(void){
		if (USB_Keyboard_Buffer[1]&Modifier_Keys_Mask[Row_Number]) return 0;
		return 1;
};
//////////////////////////////////////////////////////////////////////////////
int Is_Modifier_Key_In_HID_Keyboard_Buffer_Old(void){
		if (USB_Keyboard_Buffer_Old[1]&Modifier_Keys_Mask[Row_Number]) return 1;
		return 0;
};
//////////////////////////////////////////////////////////////////////////////

int Antighosting_Check(void){
	/*condition of ghosting: 
	At least three buttons must be pressed, the first of which is in the scanned
	column, the second in the same row as the first, and the third in the same column as
	second.*/
	//if pressed 2 buttons on one row
	if (Rows_Counters[Row_Number]){
		for (int i = 1; i <= 5; i++){
			if (Key_State[Row_Number][i]){
				for (int j = 1; j <= 5; j++){
					if ((Key_State[j][i])&&(j!=Row_Number)) return 0;
				}
			}
		}
	}
	//if pressed 2 buttons on one column
	if (Cols_Counters[Col_Number]){
		for (int i = 1; i <= 5; i++){
			if (Key_State[i][Col_Number]){
				for (int j = 1; j <= 5; j++){
					if ((Key_State[i][j])&&(j!=Col_Number)) return 0;
				}
			}	
		}
	}
//if two buttons are pressed diagonally
	if ((Cols_Counters[Col_Number] >= 1)&&(Rows_Counters[Row_Number] >= 1)) return 0;
	return 1;
};
////////////////////////////////////////////////////////////////////////////////
void Keyboard_Send_Data_Handle(void){
		Clone_Array(USB_Keyboard_Buffer, USB_Keyboard_Buffer_Old);
		if (!Is_Array_NULL(USB_Keyboard_Buffer)){
			Send_Keyboard_USB_Data();
			*Is_Empty_Array_Send_Ptr = 0;	
		}
		HAL_Delay(8);
		if ((Is_Array_NULL(USB_Keyboard_Buffer)) && (*Is_Empty_Array_Send_Ptr == 0)){
			Send_Keyboard_USB_Data();
			*Is_Empty_Array_Send_Ptr = 1;
			if (Keyboard_Send_Report_Status){*Is_Empty_Array_Send_Ptr = 0;}
			Led_OFF;
		}		
};
/////////////////////////////////////////////////////////////////////////////
void Polling_Old_Usual_Buttons(void){
	if ((Is_Usual_Key_In_HID_Keyboard_Buffer_Old())&&(Antighosting_Check())){
		USB_Data_Usual_Keys_Update();
	}
};
/////////////////////////////////////////////////////////////////////////////
void Polling_Old_Modifier_Buttons(void){
	if ((Is_Modifier_Key_In_HID_Keyboard_Buffer_Old())&&(Antighosting_Check())){
		USB_Data_Modifier_Keys_Update();
	}
};
/////////////////////////////////////////////////////////////////////////////
void Polling_New_Usual_Buttons(void){
	if ((Keys_Counter <= 8)&&(Is_Usual_Key_In_HID_Keyboard_Buffer())&&(Antighosting_Check())){
		USB_Data_Usual_Keys_Update();
	}
};
/////////////////////////////////////////////////////////////////////////////
void Polling_New_Modifier_Buttons(void){
	if ((Is_Modifier_Key_In_HID_Keyboard_Buffer())&&(Antighosting_Check())){
		USB_Data_Modifier_Keys_Update();
	}
};
/////////////////////////////////////////////////////////////////////////////
void Send_Keyboard_USB_Data(void){
	*Keyboard_Send_Report_Status_Ptr = USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, USB_Keyboard_Buffer, 9);
}
/////////////////////////////////////////////////////////////////////////////
