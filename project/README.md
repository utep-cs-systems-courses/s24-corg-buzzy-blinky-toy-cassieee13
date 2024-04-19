Lab 2: Blinky-Buzzy Toy by Cassandra Alvarez

For Lab 2, I have turned my msp430 into a "toy". This toy does different LED
patterns and utilizes the speaker to make different sounds when a different
button is pressed.

* When you press the S1 button on the green board, the red and green
  LEDs will alternate from blinking and dimming. The specific alternation is:
  when the button is first pressed the green LED will slowly dim while the red
  LED will be blinking once per second. When the green led has dimmed all the
  way, both LEDs illuminate and the red LED starts to dim while the green LED
  blinks once per second. If any other button is pressed, this LED pattern is
  interrupted.

* When you press the S2 button on the green board, the red and green LEDs do a
  simple switch off. Specifically, the green LED is illuminated alone when the
  button is first pressed, then when the button is pressed again, the red LED
  is illuminated and the green LED turns off. This pattern continues as you
  press the button.

* When you press the S3 button on the green board, initially, the buzzer will
  go off to the tone of a c note (I referenced a github code:
  https://github.com/AbhishekGhosh/Arduino-Buzzer-Tone-Codes/blob/master/Twinkle-Twinkle-Little-Star.ino
  the buzzer will continue to make sound until you press the button
  again. After pressing the button a second time the next note will
  sound. This button plays tones to the sound of Do Re Mi Fa So La Ti Do. Once
  it reaches its eighth button press, the buzzer is instructed to turn off. 

* When you press the S4 button on the green board a tone will play on the
  buzzer and the green LED will illuminate. The second button press will play
  a higher tone and make the red LED illuminate and the green LED turn off. It
  will play in this pattern for 6 button presses, then turn off with no LEDs
  on.

