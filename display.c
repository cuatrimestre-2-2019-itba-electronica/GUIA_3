#include "display.h"

bool display_init(){
	gpioMode(PIN_CSEGA, OUTPUT);
	gpioMode(PIN_CSEGB, OUTPUT);
	gpioMode(PIN_CSEGC, OUTPUT);
	gpioMode(PIN_CSEGD, OUTPUT);
	gpioMode(PIN_CSEGE, OUTPUT);
	gpioMode(PIN_CSEGF, OUTPUT);
	gpioMode(PIN_CSEGG, OUTPUT);
	gpioMode(PIN_CSEGDP, OUTPUT);
	gpioMode(PIN_SE10, OUTPUT);
	gpioMode(PIN_SE11, OUTPUT);

	cseg = 0x00;

	return true;
}

void display_show(){
	display_CSEG_show(PIN_CSEGA, cseg & display_CSEGA_Msk);
	display_CSEG_show(PIN_CSEGB, cseg & display_CSEGB_Msk);
	display_CSEG_show(PIN_CSEGC, cseg & display_CSEGC_Msk);
	display_CSEG_show(PIN_CSEGD, cseg & display_CSEGD_Msk);
	display_CSEG_show(PIN_CSEGE, cseg & display_CSEGE_Msk);
	display_CSEG_show(PIN_CSEGF, cseg & display_CSEGF_Msk);
	display_CSEG_show(PIN_CSEGG, cseg & display_CSEGG_Msk);
	display_CSEG_show(PIN_CSEGDP, cseg & display_CSEGDP_Msk);
}

void display_CSEG_show(int PIN_CSEG, int PIN_LEVEL){
	if(PIN_LEVEL!=0){
		gpioWrite(PIN_CSEG, HIGH);
	}
	else{
		gpioWrite(PIN_CSEG, LOW);
	}
}

void display_set_cseg(unsigned int num){
	switch(num){
		case 0:
			cseg = 0x3F;
			break;
		case 1:
			cseg = 0x06;
			break;
		case 2:
			cseg = 0x5B;
			break;
		case 3:
			cseg = 0x4F;
			break;
		case 4:
			cseg = 0x66;
			break;
		case 5:
			cseg = 0x6D;
			break;
		case 6:
			cseg = 0x7D;
			break;
		case 7:
			cseg = 0x07;
			break;
		case 8:
			cseg = 0x7F;
			break;
		case 9:
			cseg = 0x6F;
			break;
		default:
			cseg = 0x00;
			break;
	}
}
