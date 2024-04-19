#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "timerLibrary/libTimer.h"

//global vars
int redDims = 0;
int redBlinks = 0;
int secondCount = 0;
int blinkLimit = 5;
int blinkCount = 0;
int green = 0;
char note = 'c';

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
    else if( switch_state_down == 2){
      //P1OUT &= LED_GREEN;
      //toggle both leds every time you press S2
      if(green){
	P1OUT &= LED_RED;
	P1OUT ^= LED_GREEN;
	green = 0;
      }
      else{
	P1OUT ^= LED_GREEN;
	P1OUT &= ~LED_RED;
	green = 1;
      }
    }
    else if(switch_state_down == 3){
      switch (note){
      case 'c':
	buzzer_set_period(1915);
	note = 'd';
	break;
      case 'd':
	buzzer_set_period(1700);
	note = 'e';
	break;
      case 'e':
	buzzer_set_period(1519);
	note = 'f';
	break;
      case 'f':
	buzzer_set_period(1432);
	note = 'g';
	break;
      case 'g':
	buzzer_set_period(1275);
	note = 'a';
	break;
      case 'a':
	buzzer_set_period(1136);
	note = 'b';
	break;
      case 'b':
	buzzer_set_period(1014);
	note = 'C';
	break;
      case 'C':
	buzzer_set_period(956);
	note = 'x';
	break;
      case 'x':
	buzzer_set_period(0);
	note = 'c';
	break;
      }
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

  
