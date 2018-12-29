---
layout: page
title: Creating a reset button on the Pi
---

*Written by Anna Zeng*

To reboot the Pi without unplugging and replugging in the USB-to-Serial Dongle, we will make use of the reset pins on the Pi.
In this guide, we will solder the headers to the spot circled in red, then use jumpers to connect both ends to a button.
(Or, really, anything that triggers a reset like a switch, the DTR pin, etc.)

[<img title="Things you will need" src="../images/reset.pin.ingredients.jpg" width="400">](../images/reset.pin.ingredients.jpg)

After you have attained two headers and found the place to put the headers, place the pins into the Pi's reset pin.

[<img title="Pin placement" src="../images/reset.pin.placement.jpg" width="400">](../images/reset.pin.placement.jpg)

Now, turn on the soldering iron to about 600 degrees F (60 on the dial), and wait until the light blinks rapidly.

[<img title="Soldering Light" src="../images/reset.pin.solder.light.jpg" width="400">](../images/reset.pin.solder.light.jpg)

While holding the soldering iron like a pen, on the foam, hold the solder on one side of the pin you wish to apply solder to, and hold the soldering iron on the other side.

[<img title="Soldering Position" src="../images/reset.pin.soldering.jpg" width="400">](../images/reset.pin.soldering.jpg)

[<img title="Soldering Action" src="../images/reset.pin.action.jpg" width="400">](../images/reset.pin.action.jpg)

Once the liquid solder has covered both the Raspberry Pi's electric contacts and the pin, remove the soldering iron and the solder. Repeat for the second pin! The contacts will look sort of like this:

[<img title="Finished Soldering" src="../images/reset.pin.done.jpg" width="400">](../images/reset.pin.done.jpg)

Now connect the pins to a button on your breadboard like so:

[<img title="Button connected to reset" src="../images/reset.pin.button.jpg" width="400">](../images/reset.pin.button.jpg)

Whenever you push a button and release it, you will restart the Raspberry Pi!

Instead of connecting to a button with that jumper cable, you can connect one of the pins you soldered to the DTR pin on your USB-to-Serial dongle. We have updated `rpi-install.py` to automatically trigger your Pi to restart, by pulling the DTR pin to ground.