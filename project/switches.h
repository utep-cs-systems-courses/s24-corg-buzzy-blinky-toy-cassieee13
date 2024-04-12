#ifndef switches_included
#define switches_included

#define S1 BIT0 //S1 on the green board, p2.0
#define S2 BIT1 //S2 on the green board, p2.1
#define S3 BIT2 //S3 on the green board, p2.2
#define S4 BIT3 //S4 on the green board, p2.3
#define SWITCHES (S1 | S2 | S3 | S4 ) 

void switch_init();
void switch_interrupt_handler();

//booleans
extern char switch_state_down, switch_state_changed;

#endif //included
