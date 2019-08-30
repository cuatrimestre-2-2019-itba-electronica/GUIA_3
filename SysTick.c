#include "systick.h"
#include "hardware.h"

static void (*callBack)(void);

bool SysTick_Init (void (*funcallback)(void))
{
	SysTick->CTRL = 0x00;
	SysTick->LOAD = SYSTICK_ISR_FREQUENCY_HZ - 1;
	SysTick->VAL = 0x00;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
					SysTick_CTRL_TICKINT_Msk |
					SysTick_CTRL_ENABLE_Msk;

	callBack = funcallback;

	return 1;
}

__ISR__ SysTick_Handler (void)
{
	callBack();
}
