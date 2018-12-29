---
layout: page
title: 'Lab 7: Interrupts Check-in'
permalink: /labs/lab7/checkin/
---

During lab, we encourage you to check your understanding with a TA after completing a section or two, while the material is still fresh in your mind.

Each question below is a diagnostic question for each section of the lab. Try answering one after finishing each section to test your understanding.

1. What assembly function (in `start.s`) does your Raspberry Pi boot into and
   what does it do? This function also calls another function in `cstart.c`; what
   does that do?

2. Name two disadvantages, and one advantage, that the spin-loop implementation
   of detecting button presses has or would have over an interrupt based
   implementation.

3. What happens if the interrupt event is not cleared before returning from the
   handler?

4. Why might you want to enqueue/dequeue and then return instead of just doing
   arbitrary logic (like drawing on the screen) in the interrupt handler?

5. Show the TA that pressing and releasing buttons causes your counters to
   increase and suggest a reason why it might not match up with how many times
   you press or release the buttons.

Before leaving the lab, check in with a TA and discuss any challenges to answering the questions in the lab. If you do not feel confident about your responses, please ask us about it too!
