#include "mygpio.h"
#include "MK64F12.h"

//getPEPS
//devuelve en el arreglo de char devuelvo en la posicion 0 PE y en la posicion 1 PS
//
static PORT_Type * ports[] = PORT_BASE_PTRS;
static GPIO_Type * GPIOs[] = GPIO_BASE_PTRS;
static uint32_t sim_port[] = {SIM_SCGC5_PORTA_MASK, SIM_SCGC5_PORTB_MASK, SIM_SCGC5_PORTC_MASK, SIM_SCGC5_PORTD_MASK, SIM_SCGC5_PORTE_MASK};

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
	char peps[2];//posicion 0 pe y posicion 1 ps
	getPEPS(peps,mode);//calculo los flags ps y pe de acuerdo al modo



	ports[pinPort]->PCR[pinBit] = 0;
	SIM->SCGC5 |= sim_port[pinPort]; //Habilito el clock al puerto correspondiente
	ports[pinPort]->PCR[pinBit]|= PORT_PCR_MUX(1); //Configuro el mux del pin para que apunte al GPIO
	ports[pinPort]->PCR[pinBit]|= PORT_PCR_IRQC(0); //DESHABILITO INTERRUPCIONES

	if(mode==OUTPUT) {
		GPIOs[pinPort]->PDDR |= OUTPUT<<pinBit;
	}
	else {
		GPIOs[pinPort]->PDDR &= ~(1<<pinBit);// not tiene mucho sentido usar la mascara xq son todos unos
		ports[pinPort]->PCR[pinBit]|= PORT_PCR_PS(peps[1]);//seteo la impedancia del pin
		ports[pinPort]->PCR[pinBit]|= PORT_PCR_PE(peps[0]);//
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


bool MYgpioIRQ (pin_t pin, uint8_t irqMode, pinIrqFun_t irqFun) {
	int pinPort = PIN2PORT(pin);
	int pinBit = PIN2NUM(pin);
	int * port_irqn = PORTA_IRQn;

	ports[pinPort]->PCR &= ~PORT_PCR_IRQC_MASK;
	ports[pinPort]->PCR |= PORT_PCR_IRQC(irqMode);
	NVIC_EnableIRQ(port_irqn[pinPort]);

	return 0;
}
