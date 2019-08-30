/***************************************************************************//**
  @file     display.h
  @brief    Display driver
  @author   Arturo
 ******************************************************************************/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "gpio.h"
#include <stdbool.h>

/* Pins defines */
#define PIN_CSEGA 	PORTNUM2PIN(PE,26)
#define PIN_CSEGB 	PORTNUM2PIN(PE,26)
#define PIN_CSEGC 	PORTNUM2PIN(PE,26)
#define PIN_CSEGD 	PORTNUM2PIN(PE,26)
#define PIN_CSEGE 	PORTNUM2PIN(PE,26)
#define PIN_CSEGF	PORTNUM2PIN(PE,26)
#define PIN_CSEGG 	PORTNUM2PIN(PE,26)
#define PIN_CSEGDP 	PORTNUM2PIN(PE,26)

#define PIN_SE10 	PORTNUM2PIN(PE,26)
#define PIN_SE11 	PORTNUM2PIN(PE,26)

/* cseg register(?) */
static uint8_t cseg;

/* Masks */

#define display_CSEGA_Pos          	0U
#define display_CSEGA_Msk 			(1UL << display_CSEGA_Pos)

#define display_CSEGB_Pos          	1U
#define display_CSEGB_Msk 			(1UL << display_CSEGB_Pos)

#define display_CSEGC_Pos          	2U
#define display_CSEGC_Msk 			(1UL << display_CSEGC_Pos)

#define display_CSEGD_Pos          	3U
#define display_CSEGD_Msk 			(1UL << display_CSEGD_Pos)

#define display_CSEGE_Pos          	4U
#define display_CSEGE_Msk 			(1UL << display_CSEGE_Pos)

#define display_CSEGF_Pos          	5U
#define display_CSEGF_Msk 			(1UL << display_CSEGF_Pos)

#define display_CSEGG_Pos          	6U
#define display_CSEGG_Msk 			(1UL << display_CSEGG_Pos)

#define display_CSEGDP_Pos          7U
#define display_CSEGDP_Msk 			(1UL << display_CSEGDP_Pos)

bool display_init(); // Init display

void display_show(); // Show cseg

void display_set_cseg(unsigned int num); // Set cseg

void display_CSEG_show(int PIN_CSEG, int PIN_LEVEL); // Set pin to High or Low

#endif // _DISPLAY_H_
