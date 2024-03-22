#ifndef led_included
#define led_included

//on my msp430, the green pin and red pins were different than the provided code.
#define LED_GREEN BIT0  //P1.0
#define LED_RED BIT6    //P1.6
#define LEDS (BIT0 | BIT6)

#endif //included
