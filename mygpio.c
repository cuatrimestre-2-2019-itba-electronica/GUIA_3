#include "mygpio.h"
#include "MK64F12.h"

//getPEPS
//devuelve en el arreglo de char devuelvo en la posicion 0 PE y en la posicion 1 PS
//
void getPEPS(char peps[2], uint8_t mode){
		switch(mode){
		case INPUT:
			peps[0]=0;
			peps[1]=0;
			break;
		case INPUT_PULLUP:
			peps[0]=1;
			peps[1]=1;
			break;
		case INPUT_PULLDOWN:
			peps[0]=1;
			peps[1]=0;
			break;
		default:
			peps[0]=0;
			peps[1]=0;
			break;
		}
}

void MYgpioMode (pin_t pin, uint8_t mode){
	int pinPort = PIN2PORT(pin);
	int pinBit = PIN2NUM(pin);
	char peps[2];// posicion 0 pe y posicion 1 ps
	getPEPS(peps,mode);//calculo los flags ps y pe de acuerdo al modo


	switch(pinPort){
	case PA:
		SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;//Habilito el clock al puerto correspondiente
		PORTA->PCR[pinBit]|=PORT_PCR_MUX(1);//Configuro el mux del pin para que apunte al GPIO
		PORTA->PCR[pinBit]|=PORT_PCR_IRQC(0);//DESHABILITO INTERRUPCIONES
		if(mode==OUTPUT){
			GPIOA->PDDR|=OUTPUT<<pinBit;
		}else{
			GPIOA->PDDR&=!(1<<pinBit);// not tiene mucho sentido usar la mascara xq son todos unos
			PORTA->PCR[pinBit]|=PORT_PCR_PS(peps[1]);//seteo la impedancia del pin
			PORTA->PCR[pinBit]|=PORT_PCR_PE(peps[0]);//
		}
		break;

	case PB:
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
		PORTB->PCR[pinBit]|=PORT_PCR_MUX(1);
		PORTB->PCR[pinBit]|=PORT_PCR_IRQC(0);
		if(mode==OUTPUT){
			GPIOB->PDDR|=OUTPUT<<pinBit;
		}else{
			GPIOB->PDDR&=!(1<<pinBit);// not tiene mucho sentido usar la mascara xq son todos unos
			PORTB->PCR[pinBit]|=PORT_PCR_PS(peps[1]);//seteo la impedancia del pin
			PORTB->PCR[pinBit]|=PORT_PCR_PE(peps[0]);//
		}
		break;

	case PC:
		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
		PORTC->PCR[pinBit]|=PORT_PCR_MUX(1);
		PORTC->PCR[pinBit]|=PORT_PCR_IRQC(0);
		if(mode==OUTPUT){
			GPIOC->PDDR|=OUTPUT<<pinBit;
		}else{
			GPIOC->PDDR&=!(1<<pinBit);// not tiene mucho sentido usar la mascara xq son todos unos
			PORTC->PCR[pinBit]|=PORT_PCR_PS(peps[1]);//seteo la impedancia del pin
			PORTC->PCR[pinBit]|=PORT_PCR_PE(peps[0]);//
		}
		break;

	case PD:
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
		PORTD->PCR[pinBit]|=PORT_PCR_MUX(1);
		PORTD->PCR[pinBit]|=PORT_PCR_IRQC(0);
		if(mode==OUTPUT){
			GPIOD->PDDR|=OUTPUT<<pinBit;
		}else{
			GPIOD->PDDR&=!(1<<pinBit);// not tiene mucho sentido usar la mascara xq son todos unos
			PORTD->PCR[pinBit]|=PORT_PCR_PS(peps[1]);//seteo la impedancia del pin
			PORTD->PCR[pinBit]|=PORT_PCR_PE(peps[0]);//
		}
		break;

	case PE:
		SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
		PORTE->PCR[pinBit]|=PORT_PCR_MUX(1);
		PORTE->PCR[pinBit]|=PORT_PCR_IRQC(0);
		if(mode==OUTPUT){
			GPIOE->PDDR|=OUTPUT<<pinBit;
		}else{
			GPIOE->PDDR&=!(1<<pinBit);// not tiene mucho sentido usar la mascara xq son todos unos
			PORTE->PCR[pinBit]|=PORT_PCR_PS(peps[1]);//seteo la impedancia del pin
			PORTE->PCR[pinBit]|=PORT_PCR_PE(peps[0]);//
		}
		break;
	}

}

void MYgpioWrite (pin_t pin, bool value){

	if(value)
	{
		MYgpioSet(pin);
	}
	else
	{
		MYgpioClear(pin);
	}

}


void MYgpioToggle (pin_t pin){
	int pinPort = PIN2PORT(pin);
	int pinBit = PIN2NUM(pin);
	switch(pinPort){
	case PA:
		GPIOA->PTOR|=1<<pinBit;
		break;
	case PB:
		GPIOB->PTOR|=1<<pinBit;
		break;
	case PC:
		GPIOC->PTOR|=1<<pinBit;
		break;
	case PD:
		GPIOD->PTOR|=1<<pinBit;
		break;
	case PE:
		GPIOE->PTOR|=1<<pinBit;
		break;
	}
}


void MYgpioSet (pin_t pin){
	int pinPort = PIN2PORT(pin);
	int pinBit = PIN2NUM(pin);
	switch(pinPort){
	case PA:
		GPIOA->PSOR|=1<<pinBit;
		break;
	case PB:
		GPIOB->PSOR|=1<<pinBit;
		break;
	case PC:
		GPIOC->PSOR|=1<<pinBit;
		break;
	case PD:
		GPIOD->PSOR|=1<<pinBit;
		break;
	case PE:
		GPIOE->PSOR|=1<<pinBit;
		break;
	}
}

void MYgpioClear (pin_t pin){
	int pinPort = PIN2PORT(pin);
	int pinBit = PIN2NUM(pin);
	switch(pinPort){
	case PA:
		GPIOA->PCOR|=1<<pinBit;
		break;
	case PB:
		GPIOB->PCOR|=1<<pinBit;
		break;
	case PC:
		GPIOC->PCOR|=1<<pinBit;
		break;
	case PD:
		GPIOD->PCOR|=1<<pinBit;
		break;
	case PE:
		GPIOE->PCOR|=1<<pinBit;
		break;
	}
}


bool MYgpioRead (pin_t pin){
	int pinPort = PIN2PORT(pin);
	int pinBit = PIN2NUM(pin);
	switch(pinPort){
	case PA:
		return (PTA->PDIR & (1 << pinBit));
		break;
	case PB:
		return (PTB->PDIR & (1 << pinBit));
		break;
	case PC:
		return (PTC->PDIR & (1 << pinBit));
		break;
	case PD:
		return (PTD->PDIR & (1 << pinBit));
		break;
	case PE:
		return (PTE->PDIR & (1 << pinBit));
		break;
	}

	return false;
}
