---
layout: page
title: 'Project Guide'
permalink: /assignments/project/
released: true
---

The final assignment is a project of your own choosing. 
The goal of the project is to consolidate 
your knowledge of the key concepts in CS107e,
and to do something creative with your Raspberry Pi.

You have over two weeks to complete the project. 
There are a few important deliverables:

1. **Project team formation: due 11:59pm Thursday, November 15**

   Form a team of 1 to 3 people. In our experience, 2 is best.
   Add the Github usernames of your team members to this 
   [Google form](https://tinyurl.com/cs107e-project-fall) so that we can
   create a repository for your team.

2. **Project description: due 11:59pm Thursday, Nov 29**

   You should receive an email from GitHub indicating that your repository has
   been initialized. The initial repository will contain a single file:
   `proposal.md`. Clone your project repository and edit this file to add your
   project proposal. When you are finished, push it to GitHub.

   The project proposal should include:

   - Name of the project
   - Team members and their responsibilities
   - Goal of the project
   - Milestone for week 10 (1 week left to finish)
   - Resources needed

   Each project team has a budget of $20 per person for hardware.
   Please send us an email if you would like to buy anything.
   Be aware that if you need to mail order parts, it can take time,
   so figure out what you need ASAP and place the order.
   Also, you should first check the list of sensors we already have 
   on hand (see below).

   Each team member should be responsible for a clearly
   identifiable part of the project.

3. **Project labs**

   We will still have labs the two weeks leading up to the
   project demonstration.
   These labs will be a good time to check-in with the
   course staff; they are eager to help you create a great project.
   In the second lab, we will check whether you have made
   your milestone.
   Please don't wait until the last minute to get started on your project.

4. **Project demonstration: Fri, Dec. 14, 8:30 AM-11:30 AM, Gates B21**

   We will have a class demo day for all projects.
   The demos are scheduled during the final exam period.
   Each group should prepare a short demonstration of the project.

5. **Project code and writeup: due Fri, Dec. 14 at 8:30 AM**

   You should be using the github repository for coordinating the
   work amongst your team.
   As such, you should be regularly checking in and out code.
   The final commit of your code must be received by 11:59 pm on Wed June 13.

   Create a short writeup about your project
   and place it in README.md.
   If you have used code or ideas from other people,
   please attribute their work.
   It's fine to use code from online,
   but you must reference where you got the code,
   and what changes you made.
   It should be clear what you did, and what others did.

   The writeup should also include a short description of what
   work was performed by each member of the team.

## Extra materials

Beyond what you've seen in the course, we have some additional
materials which you can use in the final project.

### Sensors

We have
[a number of different hardware sensors](sensors)
which you could use for your project; they're available for you to
check out in lab. Let us know if you'd like to use one of them.

### Support code

The Raspberry Pi has on-board SPI and I2C controllers, which you can use to
communicate with many kinds of sensors and devices that speak those protocols.
For example, if you want to have analog input, we have an analog-to-digital
converter, the MCP3008, which would communicate over a SPI interface with your Pi.
You are welcome to write your own SPI or I2C driver for your device as part of your
project. However, if 
you would like to use an existing implementation, there are versions in libpi that 
you are free to use (make sure to cite that you used these implementations).

libpi also contains an experimental filesystem interface
which you can use to interact with the files on the SD card. This enables you to
do operating-system-like things, like maybe run programs off the card,
or store large data files without having to copy them over the
bootloader every time, or save documents.

### Part Suppliers

Here are some good vendors for electronics hardware.

* [Jameco](https://www.jameco.com/) 
Jameco has a great selection of electronic parts.
They are also located in Burlingame near SFO. 
If you order from them,
normal mail via the postal service will arrive the next day.
If you have a car, 
you can also drive up there and pick up parts at the *Will Call*.

* [Pololu](https://www.pololu.com/)
Has a wide selection of parts for robotics,
including sensors and motor drivers.
They also document their parts very well.

* [Adafruit](https://www.adafruit.com/)
Limor Fried has founded a company devoted that caters
to makers of all types.
Besides building great products,
they also have extensive tutorials and learning guides.

* [Sparkfun](https://www.sparkfun.com/)
Another great source for hobbiest electronics.

For basic electronics such as transistors, op-amps,
you should also check out 
[lab64](https://ee.stanford.edu/student-resources/lab64),
the EE Department Maker Space.


## Past projects

Here are some projects from past years:

* Noob Cube
  - Graphical viewer for a 3D wireframe
* Pi Selfie Mirror
  - Take a selfie with animations displayed on a mirror-monitor
* Chess but cool
  - Chess board that can record & visualize moves on a screen (using Hall-effect sensors)
* Threading system
  - Build threading system so Pi can simulate running code in parallel
* Pi-ke
  - Bike system with indicator lights, user display
* Keyboard Orchestra
  - Record/play music using keyboard
* Sunlight lamp
  - Lamp that mirrors natural sunlight intensity throughout day
* Raspberry Pi Bongos
  - Electronic drumset with piezoelectric vibration sensors
* SPI Network with Slave-Slave communication
  - Communication between Pis (display received data, store to memory, run received code)
* The Fruit Ninjas
  - Fruit-ninja inspired game controlled by user hand gestures (sonar sensors)
* Theremins visualized
  - Translate time-of-flight distance to pitch and output sound and visualization
* Synthetic Music
  - Sythetic instrument using piezo sensors on fingers, and output sound and visualization
* Electronic dress
  - Dress which lights up with electroluminescent wires when you move
    (based on gyroscope)
* Extended etch-a-sketch
  - Takes input from two knobs, accelerometer, and push buttons:
    controls menu UI and paint program
* ArduCAM
  - A library to access ArduCAM with the Raspberry Pi, along with a
    shell to enter commands (filters, camera settings) and display
    output
* Robo-Turle
  - A robotic turtle with servo motors and ultrasonic sensor (for
    self-driving), controllable with an NES controller
* Game Boy emulator
* Raspberry Pi GPU
  - An assembler which targets the Pi GPU, some sample assembly
    programs, and a guide to using the GPU from bare metal
* Intruder detection system
  - Uses 8 passive infrared sensors around the room to detect motion
* DMX lighting console and receiver
  - User interface to see lighting data, plus commands like setting
    light color, setting intensity, patching the light, changing the
    fixture type
* 2-player basketball arcade game
  - Uses Apple remote to choose time to play, then uses IR sensor to
    check when ball goes into basket. Sounds buzzer when a player
    scores.
* Sensor visualizer
  - Car dashboard-like visualization of MCP3008 ADC, including a GL
    library

Talk to the course staff if you want more information or you think you
could use code from one of these projects.

## Project suggestions

The best projects are ones that you think of yourself.
Feel free to browse the internet in search of cool things to do.
Some good sources are [hackaday.com](http://hackaday.com) and 
[adafruit.com/blog](https://blog.adafruit.com).

### Game

You have the start of a graphics and input library.
Extend your graphics library to draw additional types of objects,
and your input library to handle a game controller.

Some examples of input devices that you could use to control your game:

- A homebrew game pad made of buttons. Most game pads have
two buttons (A and B) for game control,
and 4 buttons used as a d-pad (left, right, up, down).

- Your PS/2 keyboard and/or mouse.

- Atari 2600 paddle controllers (or other paddle controllers).

- Old-school NES, SNES, or other simple gamepads with simple digital protocols.

Once you have better input, you are all set to build a game.
Build a simple game such as Pong or Tetris,
or even better a game of your own design.

Another cool thing you can do is communicate with old game cartridges, since you
can connect the pins on the cartridge to the GPIO pins on the Pi.

### Music

We described how to generate notes on the Raspberry Pi.
With that knowledge, you can 

- Create a simple music player that allows the user 
to choose from a list of simple melodies.
Add buttons on a breadboard for control (skip, pause, play, volume?)

- Turn your keyboard into a music keyboard,
so that keys play individual notes and pressing multiple keys 
at the same time combines the notes.
Use a combination of timers and low-level keyboard access 
to enable you to record and then loop tracks.

- Take a music synthesizer such as the Korg Monotron 
and hack it to add MIDI support with one Pi,
then have a second Pi control it over MIDI.
Alternatively, build your own music synthesizer.

## System components

Your project should be about building a working system that does something cool.

However, if you build some support infrastructure,
then you can build a more impressive system.
A good sub-project for a team member
is to build a component of the system.

### Analog input

Up to now, we have only read digital values using GPIO.
The Raspberry Pi, unlike a microcontroller like an Arduino,
cannot read analog values.

Many sensors are analog:
  - Photodetectors
  - Potentiometers
  - Temperature sensors
  - Joysticks

In order to read analog values, you will need to interface an analog
to digitial convertor (ADC) to the Raspberry Pi.  An example of an ADC
is the MCP3008, which can be controlled from the PI using the Serial
Peripheral Interface (SPI) protocol.

Write a program that uses some
analog inputs to produce an interesting result, such as a screen
visualization or sound.

### Network (Ambitious)

Build a simple network that allows multiple raspberry pis to communicate
over a shared medium (only one Pi can transmit at a time).
One way to do this is to connect TX and RX pins to a
shared line.

It is also possible to communicate by other means.
For example, you could use sound, light, or radio waves.

Finally, you've seen in class how "digital" lines aren't purely digital.
You could design your circuit to make bits as sharp as possible to see how
fast you can transmit and receive. You might find that sending bits faster
means you'll have to send smaller packets, so optimize for overall data
transfer, not just the bit rate.

### GPU (Ambitous)

The raspberry pi has a very powerful GPU.
In fact, the GPU is much faster than the CPU.
The GPU assembly language is similar to,
but different,
than the CPU assembly language.
It is possible to download code to the GPU using a mailbox,
and then call that code.
Learn about the GPU and build a library for programming the GPU.

Can you think of a computationally intensive task 
that could be off-loaded to the GPU? At the very least, you can clear your
screen buffer faster!
