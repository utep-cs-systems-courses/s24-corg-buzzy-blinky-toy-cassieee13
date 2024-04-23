#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "timerLibrary/libTimer.h"

//global vars
char redDims = 0; //boolean
char redBlinks = 0; //boolean
int secondCount = 0;
int blinkLimit = 5;
int blinkCount = 0;
char green = 0; //boolean
char note = 'c'; //used for button S3
int fireCount = 0;

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
      //toggle both leds every time you press S2
      if(green){
	P1OUT ^= LED_RED;
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
      /*
       This Switch statement executes when S3 is pressed. After each button press occurs, a different note will play. 
The notes are defined on buzzer.h and I use the buzzer_set_period() that takes an integer as parameter. */
      switch (note){
      case 'c':
	buzzer_set_period(LITTLE_C);
	note = 'd';
	break;
      case 'd':
	buzzer_set_period(D);
	note = 'e';
	break;
      case 'e':
	buzzer_set_period(E);
	note = 'f';
	break;
      case 'f':
	buzzer_set_period(F);
	note = 'g';
	break;
      case 'g':
	buzzer_set_period(G);
	note = 'a';
	break;
      case 'a':
	buzzer_set_period(A);
	note = 'b';
	break;
      case 'b':
	buzzer_set_period(B);
	note = 'C';
	break;
      case 'C':
	buzzer_set_period(BIG_C);
	note = 'x';
	break;
      case 'x':
	buzzer_set_period(0);
	note = 'c';
	break;
      }
    }
    else if( switch_state_down == 4){
      int num = fireCount % 2; //either 1 or 0
      if(fireCount == 0){
	num = 3;
      }
      
      switch (num){
	/* When this switch statement executes, one led will flash and one tone will play. You can press the button six times, then the next button press will turn the LEDs off and the buzzer off. */
      case 0: //even: 2, 4, 6
	buzzer_set_period(800);
	P1OUT &= ~LED_RED;
	P1OUT ^= LED_GREEN;
	fireCount--;
	break;
      case 1: //odd: 1, 3, 5
	buzzer_set_period(1200);
	P1OUT &= ~LED_GREEN;
	P1OUT ^= LED_RED;
	fireCount--;
	break;
      case 3:
	buzzer_set_period(0);
	P1OUT &= ~LED_GREEN;
	P1OUT &= ~LED_RED;
	fireCount = 6;
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

  
