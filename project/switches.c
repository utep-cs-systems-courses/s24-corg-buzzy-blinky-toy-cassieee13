#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char switch_state_down, switch_state_changed; //booleans

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  //update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES); //if switch up, sense down
  P2IES &= (p2val | ~SWITCHES);//if switch down, sense up
  return p2val;
}

void
switch_init() //setup switch
{
  P2REN |= SWITCHES; //enable resistors for switches
  P2IE |= SWITCHES;  //enable interrupts from switches
  P2OUT |= SWITCHES; //pull ups for switches
  P2DIR &= ~SWITCHES; //set switches' bits for input
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  //switch_state_down = (p2val & S1) ? 0 : 1; //0 when S1 is up
  if( !(p2val & S1) ){
    switch_state_down = 1;//S1 is down or pressed
    switch_state_changed = 1;
    led_update();
  }
  else if ( !(p2val & S2) ){
    switch_state_down = 2;
    switch_state_changed = 1;
    led_update();
  }
  else if( !(p2val & S3) ){
    switch_state_down = 3;
    switch_state_changed = 1;
    led_update();
  }
  else if( !(p2val & S4) ){
  }
}
