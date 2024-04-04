#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "timerLibrary/libTimer.h"

//global vars
int redDims = 0;
int redBlinks = 0;
int secondCount = 0;
int blinkLimit = 5;
int blinkCount = 0;

void led_init()
{
  P1DIR |= LEDS; //bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update()
{
  if(switch_state_changed){
    if(switch_state_down == 1){
      enableWDTInterrupts();
      redBlinks = 1;
    }
  }
  switch_state_changed = 0;
}

void
__interrupt_vec(WDT_VECTOR) WDT()
{
  blinkCount++;
  if(blinkCount >= blinkLimit){//on for 1 interrupt period
    blinkCount = 0;
    if(redDims){
      P1OUT |= LED_RED;
    }
    else{
    P1OUT |= LED_GREEN;
    }
  }
  else{
    if(redDims){
      P1OUT &= ~LED_RED;
    }
    else{
      P1OUT &= ~LED_GREEN;//off for blinkLimit -1 interrupt periods
    }
  }
  //measure a second
  secondCount++;
  if(secondCount >= 250){
    secondCount = 0;
    blinkLimit++;
    if(redBlinks){//red blinks
      P1OUT ^= LED_RED;
      //P1OUT &= ~LED_GREEN;
      redBlinks = 0;
    }
    else{//green blinks
      P1OUT ^= LED_GREEN;
      //P1OUT &= ~LED_RED;
      redBlinks = 1;
    }
    if(blinkLimit >= 8){
      blinkLimit = 0;
      if(!redDims){
	redDims = 1;
      }
      else{
	redDims = 0;
      }
    }
  }
}

  
