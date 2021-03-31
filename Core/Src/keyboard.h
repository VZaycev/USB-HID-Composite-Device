#include "main.h"
#include "usb_device.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
	
/*Variables*/
static uint8_t Keyboard_Send_Report_Status;
//This variable contains status(USBD_OK/USBD_BUSY) of last keyboard report

static uint8_t* Keyboard_Send_Report_Status_Ptr = &Keyboard_Send_Report_Status;
//Pointer on Keyboard_Send_Report_Status(USBD_OK = 0/USBD_BUSY = 1)

static uint8_t USB_Keyboard_Buffer_Old[8] = {0};	
//An array which keeps in itself state of USB_Keyboard_Buffer in previous iteration
	
static uint8_t USB_Keyboard_Buffer[8] = {1, 0, 0, 0, 0, 0, 0, 0};
	/*An array wich is a data package for sending by USB
	and contains keys codes of keyboard*/
	
static uint8_t Is_Empty_Array_Send = 0;
	//Flag
	//True: null USB_Keyboard_Buffer is already send in last iteration
	//False: in last iteration null HID_Keyboard was not send or it was not null
	
static uint8_t* Is_Empty_Array_Send_Ptr = &Is_Empty_Array_Send;
	//Pointer on Is_Empty_Array_Send(for access a variable in functions)
				
static uint8_t Keys_Counter = 3;
	/*Variable wich counts how much buttons is already pressed.
	Max : 8. Modifier keys is not counting.*/
	
static	uint8_t* Keys_Counter_Ptr = &Keys_Counter;
	//Pointer on Keys_Counter(for access a variable in functions)
	
extern uint8_t* Keys_Counter_Ptr;
	//Pointer on Keys_Counter(for access a variable in functions)

extern uint8_t Col_Number;
	//This variable stores the number of the scanned column of the current button being scanned. 
	
extern uint8_t Row_Number;
	//This variable stores the number of the scanned row	 of the current button being scanned. 	
	
static uint8_t Keys_ID [6][5] = {
	{0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x04, 0x05, 0x06, 0x07},
	{0x00, 0x08, 0x09, 0x0A, 0x0B},
	{0x00, 0x0C, 0x0D, 0x0E, 0x18},
	{0x00, 0x10, 0x11, 0x12, 0x13},
	{0x00, 0x14, 0x15, 0x16, 0x17},
};
	/*This matrix contains key codes to be used in implementing a USB keyboard.
	The matrix is compiled in accordance with the arrangement of keys
	on the keyboard in rows and columns and their purpose*/

static uint8_t Key_State[5][5] = {
	{0},
	{0},
	{0},
	{0},
	{0},
};
	//This matrix contains the state of the buttons (pressed / released)

static uint8_t Modifier_Keys_Mask[5] = {0, 0x01, 0x02, 0x04, 0x08};
	/*This array contains masks for modifying the second byte of the buffer,
	which is responsible for the modifier buttons(shift, ctrl, win and alt) */

static uint8_t Rows_Counters[5];
	//this array contains number of pressed buttons on each row

static uint8_t Cols_Counters[5];
	//this array contains number of pressed buttons on each column

/*Functions defenitions*/

void Update_Counters(void);
//this function updates counters of rows and columns of pressed buttons

int Array_Compare(uint8_t Array1[], uint8_t Array2[]);
//this function checks if arrays are equal element by element 

int Is_Array_NULL(uint8_t Array[]);
//this function cheks if all elements are null

void Clone_Array(uint8_t Array1[], uint8_t Array2[]);
//this function copies one array to another element by element

void Clearing_Flags(void);
//this function uses for clearing all flags and counters each iterations

void USB_Data_Usual_Keys_Update (void);
//this function is responsible for the formation of an array of data for sending via usb(common buttons)

void USB_Data_Modifier_Keys_Update(void);
//this function is responsible for the formation of an array of data for sending via usb(modifier buttons)

int Is_Usual_Key_In_HID_Keyboard_Buffer(void);
//this function cheks is pressed usual key is already in USB_Keyboard_Buffer

int Is_Usual_Key_In_HID_Keyboard_Buffer_Old(void);
//this function combines in itself Is_Modifier_Key_In_HID_Keyboard_Buffer_Old and Is_Usual_Key_In_HID_Keyboard_Buffer_Old functions

int Is_Modifier_Key_In_HID_Keyboard_Buffer_Old(void);
//this function cheks is pressed usual key is alread in USB_Keyboard_Buffer_Old

int Is_Modifier_Key_In_HID_Keyboard_Buffer(void);
//this function cheks is pressed modifier key is already in USB_Keyboard_Buffer

void Keyboard_Send_Data_Handle(void);
//this function 

int Antighosting_Check(void);
//this function is used to check the possibility of a phantom press and if it is detected, this press is blocked 

void Polling_Old_Usual_Buttons(void);
/*This function checks if the conditions for the press registration are met.
Conditions: Is_Usual_Key_In_HID_Keyboard_Buffer_Old, Antighosting_Check.
If they are all observed calls function USB_Data_Usual_Keys_Update*/


void Polling_Old_Modifier_Buttons(void);
/*This function checks if the conditions for the press registration are met.
Conditions: Is_Modifier_Key_In_HID_Keyboard_Buffer_Old, Antighosting_Check.
If they are all observed calls function USB_Data_Modifier_Keys_Update*/

void Polling_New_Usual_Buttons(void);
/*This function checks if the conditions for the press registration are met.
Conditions:Keys_Counter <= 8, Is_Usual_Key_In_HID_Keyboard_Buffer, Antighosting_Check.
If they are all observed calls function USB_Data_Usual_Keys_Update*/

void Polling_New_Modifier_Buttons(void);
/*This function checks if the conditions for the press registration are met.
Conditions:Is_Modifier_Key_In_HID_Keyboard_Buffer, Antighosting_Check.
If they are all observed calls function USB_Data_Modifier_Keys_Update*/

void Send_Keyboard_USB_Data(void);
//this function send data packet with report id 1(keyboard)
