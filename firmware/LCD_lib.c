
#include "Cpu.h"
#include "E.h"
#include "RS.h"
#include "DataPins.h"
#include "LCD_lib.h"
#include <string.h>
/* Include Prototypes for your library, if applicable */
/* #include "mylibrary.h" */



/*-----------------------------------------------------------------------*

	Place your 'C' library code here.
	
 *-----------------------------------------------------------------------*/

void init(void){
	Cpu_Delay100US(1000);
	sendByteIR(0x03); //0011
	sendByteIR(0x03); //0011
	sendByteIR(0x03); //0011
	sendByteIR(0x02); //0010
	sendByteIR(0x02); //0010
	sendByteIR(0x08); //1000
	sendByteIR(0x00); //0000
	sendByteIR(0x01); //0001
	sendByteIR(0x00); //0000
	sendByteIR(0x0f); //1111
}

void sendByteDR(byte dataByte) {
	// if RS is low, set it high
	if (!RS_GetVal()) {
		RS_PutVal(1);
	}
	
	//delay
	Cpu_Delay100US(100);
	
	//set first half of dataByte
	DataPins_PutVal(dataByte >> 4); 
	
	//pulse E
	pulseE();
	
	//set second half of dataByte
	DataPins_PutVal(dataByte & 0x0F);
	
	//pulse E
	pulseE();
}

void sendNumberDR(uint32_t v) {
	uint32_t mask = 1000000000;
	char digit;
	while (mask) {
		digit = '0';
		while (v >= mask) {
			digit++;
			v -= mask;
		}
		sendByteDR(digit | 0x30);
		mask /= 10;
	}
	return;
}

void sendByteIR(byte dataByte){
		RS_PutVal(0);
		
		//delay
		Cpu_Delay100US(1);
		
		//set dataByte
		//set first half of dataByte
		DataPins_PutVal(dataByte >> 4); 
			
		//pulse E
		pulseE();
			
		//set second half of dataByte
		DataPins_PutVal(dataByte & 0x0F);
		
		//pulse E
		pulseE();
}

void pulseE(void) {
	//delay 100us
	Cpu_Delay100US(1);
	//set E high
	E_PutVal(1);
	// Delay again
	Cpu_Delay100US(1);
	//set E low 
	E_PutVal(0);
	//Delay
	Cpu_Delay100US(1);
}
