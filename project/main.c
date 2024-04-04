//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "timerLibrary/libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT |= LED_GREEN;
  P1OUT &= ~LED_RED;

  configureClocks();    /*setup master oscillator, CPU & peripheral clocks */  
  enableWDTInterrupts();/*enable periodic interrupts */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

//global state variables that control blinking
int blinkLimit = 5;//duty cycke = 1/blinkLimit
int blinkCount = 0;//cycles 0..blinkLimit -1
int secondCount = 0;//state var representing repeating time 0..1s
int redTurn = 0;//acting as a boolean

void
__interrupt_vec(WDT_VECTOR) WDT() /*250 interrupts per sec */
{
  //handle blinking
  blinkCount++;
  if( blinkCount >= blinkLimit){//on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
  }
  else{
    P1OUT &= ~LED_GREEN;//off for blinkLimit -1 interrupt periods
  }
  //measure a second
  secondCount++;
  if(secondCount >= 250){//once each sec
    secondCount = 0;
    blinkLimit++;//reduce duty cycle
    if(redTurn){//red will do the blinking
      P1OUT ^= LED_RED;
      P1OUT &= ~LED_GREEN;
      redTurn = 0;
    }
    else{//green will blink
      P1OUT ^= LED_GREEN;
      P1OUT &= ~LED_RED;
      redTurn = 1;
    }
    if(blinkLimit >= 8){//but don't let duty cycle go below 1/7
      blinkLimit = 0;
    }
  }
}

