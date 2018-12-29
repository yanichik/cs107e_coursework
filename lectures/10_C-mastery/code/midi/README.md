Sample code to control a KORG volca keys or volca beats
from the Pi. Connect the midi data line to GPIO pin 25
(through a 220Ohm resistor) and the current line to
5V through a 220Ohm resistor.

1. Makefile:
  make on its own will make midi-beat (drums on the drum kit)
  make install will make and install midi-beat
  
  make install midi-lamb will make and install midi-lamb
  
2. MIDI-in pins:
  white wire to 220ohm resistor to 5V on Pi
  red wire to 220ohm resistor to pin BCM/GPIO 25

3. For PulseView logic analyzer with DreamSourceLab DSLogic Pro:
  a. Ground goes to Pi ground
  b. Signal pin goes to red MIDI (pin 25 on Pi)
  c. Set voltage range on PulseView to 1.6V for 0/1
  d. Set UART as decoder, with 31250 baud rate (8n1)
  e. In UART, choose "Stack Decoder" and select MIDI
  
4. Actual pinout of MIDI connector:

            silver (unshielded), gnd when using logic analyzer
                    _____
                 .-'     '-.
        red    .'     o     '.  white
      (signal)/   o       o   \ (5V)
             ;                 ;
     yellow  |  o           o  |   black
   (no conn) ;                 ; (no conn)
              \               /
               '.           .'
                 '-._____.-'



Author: Philip Levis <pal@cs.stanford.edu>
Updated for new libraries by Chris Gregg <cgregg@stanford.edu>
Date: May 14, 2017
