Application that expects a button on GPIO pin 25 that connects pin 
25 to ground.
Uses a pull-up resistor, so a button press results in a falling edge. 
Displays the number of button presses on the HDMI screen. 
Uses interrupts so button presses are enqueued -- slow screen refresh
shows them spool out.
