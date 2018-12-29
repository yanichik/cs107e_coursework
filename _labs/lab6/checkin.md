---
layout: page
title: 'Lab 6: Framebuffer Check-in'
permalink: /labs/lab6/checkin/
---

During lab, we encourage you to check your understanding with a TA after completing a section or two, while the material is still fresh in your mind.

Each question below is a diagnostic question for each section of the lab. Try answering one after finishing each section to test your understanding.

1. How does your checkerboard look? Show a TA your crisp looking squares!

2. What happens if `mailbox_t mailbox` is not tagged as `volatile`?

3. Why could we `|` the `addr` and `channel` in `mailbox_write`? (Section 2)

4. Show off your memory map diagram! Where does the stack sit, relative to the
   framebuffer? Where do the GPIO registers sit relative to the mailbox? (Section 2)

5. What is the difference between the following two lines of code?

   		char *a = "Hello, world\n";
   		char b[]= "Hello, world\n";

6. Why does pixel_data have size `95 * 14 * 16 / 8`?

Before leaving the lab, check in with a TA and discuss any challenges to answering the questions in the lab. If you do not feel confident about your responses, please ask us about it too!