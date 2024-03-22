#include <msp430.h>
#include "libtimer.h"
#include "led.h"

int main(void)
{
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks(); //setup master oscillator, CPU & peripheral clocks
  enableWDTinterrupts(); //enable periodic interrupt

  or_sr(0x18); /* CPU off, GIE on */
}

int secondCount = 0; //global state var to count time

void
__interrupt_vec(WDT_VECTOR)WDT()
{
  secondCount++;
  if( secondCount >= 250){ //once per second
    secondCount = 0; //reset count
    P1OUT ^= LED_GREEN; //toggle the green LED
  }
}
