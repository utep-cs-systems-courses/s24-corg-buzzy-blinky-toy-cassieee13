#ifndef switches_included
#define switches_included

#define SW1 BIT3 //switch 1 is p1.3
#define SWITCHES SW1 //only 1 switch on this board

void switch_init();
void switch_interrupt_handler();

//booleans
extern char switch_state_down, switch_state_changed;

#endif //included
