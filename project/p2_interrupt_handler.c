#include <msp430.h>
#include "switches.h"

/*Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2()
{
  if(P2IFG & SWITCHES){//did a button cause this interrupts
    P2IFG &= ~SWITCHES; //clear pending sw interrupts
    switch_interrupt_handler(); //single handler for all switches
  }
}
