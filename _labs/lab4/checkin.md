---
layout: page
title: 'Lab 4: Linking and Loading Check-in'
permalink: /labs/lab4/checkin/
---

During lab, we encourage you to check your understanding with a TA after
completing a section or two, while the material is still fresh in your mind.

Each question below is a diagnostic question for each section of the lab. Try
answering one after finishing each section to test your understanding.

1. How does a program change during the linking process? According to `nm`,
   what segment is the `n` variable in `linking.o`, and how is it different in
   `linking.elf`? How does the instruction `bl _cstart` change after linking?

2. On a sheet of paper, with address 0x0 at the bottom of the page and
   0x8000000 at the top, sketch a diagram of the memory layout created in
   `code/linking`. Add to your diagram the contents of the stack at the point
   where execution has just entered the `main` function. (Use the `main`
   diagram from [lab3](http://cs107e.github.io/labs/lab3/images/stack_abs.html)
   as a guide.)

3. How does the bootloader work? As a group, collectively add comments to
   `bootloader.c` explaining what it does.

4. Why can't `tokenize` or `strndup` declare space for input strings in their
   stack frames?

Before leaving the lab, check in with a TA and discuss any challenges to
answering the questions in the lab. If you do not feel confident about your
responses, please ask us about it too!
