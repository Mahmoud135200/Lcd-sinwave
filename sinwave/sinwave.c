#include "LIB/BIT_Math.h"
#include "LIB/STD_Types.h"
#include "MCAL/DIO/DIO.h"
#include "HAL/LCD/LCD.h"
#include<avr/io.h>
#include <util/delay.h>

int main(){
	DIO_voidSetPortDirection(DIO_PORTA,0xff);
	LCD_voidInit();
	LCD_voidClear();
	while(1){

		LCD_voidPrintSinWave("Mahmoud");
}




	return 0;
}
