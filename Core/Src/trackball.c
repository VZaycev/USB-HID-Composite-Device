#include "trackball.h"
#define Cursor_Step 1

enum axes {X = 2, Y = 3};

Encoder Encoder_X = {0 ,0, &htim4}, Encoder_Y = {0, 0, &htim2};//Initialize of Encoder stucture
////////////////////////////////////////////////////////////////////////////////////////////////

void Get_Mouse_One_Axis_Direction(Encoder *Encoder_Exemplar){
		uint8_t Axis;
		if (Encoder_Exemplar -> htim == &htim2){
			Axis = X;
		}
		else Axis = Y;
		Encoder_Exemplar -> Current_State = __HAL_TIM_GetCounter(Encoder_Exemplar -> htim);//Getting value of timer counter
		if (Encoder_Exemplar -> Current_State == Encoder_Exemplar -> Previous_State){//if old value = new value
					USB_Mouse_Buffer[Axis] = 0;//cursor do not moving
			}
			else if (Encoder_Exemplar -> Current_State > Encoder_Exemplar -> Previous_State){//if old value > new value 
				USB_Mouse_Buffer[Axis] = -Cursor_Step;//cursor is moving down(if Y) or right(if X);			
			}
			else if (Encoder_Exemplar -> Current_State < Encoder_Exemplar -> Previous_State){//if old value < old value 
				USB_Mouse_Buffer[Axis] = Cursor_Step;//cursor is moving up(if Y) or right(if X);
			}
				Encoder_Exemplar -> Previous_State = Encoder_Exemplar -> Current_State; 			
				//HAL_Delay(1);
		};

////////////////////////////////////////////////////////////////////////////////////////////////////

void Get_Mouse_Direction(void){
		Get_Mouse_One_Axis_Direction(&Encoder_X);
		Get_Mouse_One_Axis_Direction(&Encoder_Y);
};
		
void Send_Mouse_USB_Data(void){
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, USB_Mouse_Buffer, 5);
};

void Set_Click(int Click_Value){
		USB_Mouse_Buffer[1] = Click_Value;
};
