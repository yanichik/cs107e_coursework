Timing based Analog to Digital Convertor.

The basic idea is to time how long it takes to charge a capacitor.
This technique was used in the original Pong game.

http://atariage.com/forums/blog/52/entry-392-paddles/

Woz also used this approach in the Apple 1.


Demo

1.A 2N7000 mosfet to discharge the capacitor. Writing a 1 to GPIO_3, 
turns on the mosfet and discharges the capacitor.

2. A 100K pot was connected to 3.3V from the Pi. The wiper was connected
to a 1uF capacitor. GPIO_2 was connected to the wiper-capacitor node to
measure the voltage at the capacitor. The GPIO pin is a comparitor, 
When the valtage goes above 1.67V, it reads as 1.

