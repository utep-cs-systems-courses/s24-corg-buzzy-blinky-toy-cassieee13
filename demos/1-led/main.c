//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN; //switching to |= LED_GREEN turns it on
  P1OUT |= LED_RED; //switching to &= ~LED_RED makes it turn off
  or_sr(0x18);		/* CPU off, GIE on */
}
