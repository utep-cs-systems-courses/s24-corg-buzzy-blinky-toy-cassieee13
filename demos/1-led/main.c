//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT |= LED_GREEN;//switching to P1OUT |= LED_GREEN turns green LED on 
  P1OUT |= LED_RED;   //switching to P1OUT &= ~LED_RED turns red LED off
  or_sr(0x18);		/* CPU off, GIE on */
}
