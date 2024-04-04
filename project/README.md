Lab 2: Blinky-Buzzy Toy by Cassandra Alvarez

For Lab 2, I have turned my msp430 into a "toy". This toy does different LED
patterns or utilizes the speaker to make different sounds when a different
button is pressed.

* When you press the button on the red board located at P1.3 the red and green
  LEDs will alternate from blinking and dimming. The specific alternation is:
  when the button is first pressed the green LED will slowly dim while the red
  LED will be blinking once per second. When the green led has dimmed all the
  way, both LEDs illuminate and the red LED starts to dim while the green LED
  blinks once per second. If any other button is pressed, this LED pattern is
  interrupted. 
