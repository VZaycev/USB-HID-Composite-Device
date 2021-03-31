#include "main.h"
#include "usb_device.h"
static uint8_t USB_Mouse_Buffer[7] = {2, 0, 0, 0, 0, 0, 0};
	/*An array wich is a data package for sending by USB	
	and contains X and Y axes and clicks of mouse*/

extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct Encoder_Struct {
	uint16_t Current_State;//Current state of timer counter 
	uint16_t Previous_State;//Privious state of timer counter
	TIM_HandleTypeDef* htim;//Pointer at timer stuct
}Encoder;

//Functions Declaration//

void Get_Mouse_One_Axis_Direction(Encoder *Encoder_Exemplar);
//This function calculates the direction of movement along one of the axes(X or Y);

void Get_Mouse_Direction(void);
//This function combines in itself Get_Mouse_One_Axis_Direction for X and Y axes

void Send_Mouse_USB_Data(void);
//this function send data packet with report id 2(mouse)

void Set_Click(int Click_Value);
//This function sets first element of USB_Mouse_Buffer,
//wich is responsible for mouse buttons clicks
