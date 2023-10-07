#include <avr/io.h>
#include <util/delay.h>
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"


void LCD_voidInit(void){
	/* Data port -> output*/
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0XFF);
	/* RS, RW, E  -> output */
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RS, DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, RW, DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, EN, DIO_OUTPUT);
	
	_delay_ms(35);
	LCD_voidSendCommand(FUNCTION_SET);
	_delay_us(50);
	LCD_voidSendCommand(DISPLAY_ON_OFF);
	_delay_us(50);
	LCD_voidSendCommand(CLEAR);
	_delay_ms(2);
}


void LCD_voidSendCommand(u8 Copy_u8Command){
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS, DIO_LOW);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW, DIO_LOW);
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Command);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_LOW);	
}


void LCD_voidSendChar(u8 Copy_u8Char){
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RS, DIO_HIGH);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, RW, DIO_LOW);
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Char);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, EN, DIO_LOW);
	
}

void LCD_voidSendString	(u8 *Copy_u8String){

	while( *Copy_u8String != '\0'){
		LCD_voidSendChar( *Copy_u8String);
		 Copy_u8String++;
		
	}
	
	
}

void LCD_voidSetLocation(u8 Copy_u8LineNum, u8 Copy_u8CharNum){
	
	switch(Copy_u8LineNum)
	{
	case LCD_LINE1 : LCD_voidSendCommand(0x80 + Copy_u8CharNum); break;

	case LCD_LINE2 : LCD_voidSendCommand(0xC0 + Copy_u8CharNum); break;

	}
	
}

void LCD_voidSendNumber	(u32 Copy_u32Num){
	
	u8 str[10];
	u8 i, rem, len =0;
	u32 n = Copy_u32Num;
	while(n != 0){
		len++;
		n /= 10;
	}
	for(i =0 ; i < len ;i++){
		rem = Copy_u32Num % 10;
		Copy_u32Num= Copy_u32Num / 10;
str [len - (i+1)] = rem + '0';
		
		
	}
	str [len] = '\0';
	LCD_voidSendString(str);
}

void LCD_voidDrawSpecialChar(u8 Copy_u8CharIndex, u8 *Copy_u8SpecialChar){
	
	


}

void LCD_voidSendSpecialChar(u8 Copy_u8CharIndex){
		

}
void LCD_voidClear()
{
	LCD_voidSendCommand (0x01);		// clear display
	LCD_voidSendCommand (0x80);
	_delay_ms(2);// cursor at home position
}
u8 LCD_u8SetCursor(u8 Copy_u8LineNum,u8 Copy_u8CharNum){
	
	switch(Copy_u8LineNum){
	case LCD_LINE1:LCD_voidSendCommand(0x80+Copy_u8CharNum);break;
	case LCD_LINE2:LCD_voidSendCommand(0xC0+Copy_u8CharNum);break;
	
}
}
u8 LCD_u8CalculateStringLength(u8* Copy_String){
	u8 i=0;
	while(Copy_String[i]!='\0'){
		i++;
	}
	return i;
}


void LCD_voidPrintSinWave(u8* Copy_Name){

	u8 row=LCD_LINE1 ;
  u8 column;
	for(column=0;column<=(15-LCD_u8CalculateStringLength(Copy_Name)+1);column+=4){
		LCD_u8SetCursor(row,column);
		LCD_voidSendString(Copy_Name);
        row ^= 1;
		_delay_ms(750);
		LCD_voidClear();
}
}



