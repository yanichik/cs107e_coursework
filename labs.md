---
layout: page
title: Labs
---

### List of labs

{% for lab in site.labs %}
{% unless lab.path contains 'checklist' or lab.path contains 'checkin' %}
- {% include link.html target=lab %}
{% endunless %}
{% endfor %}

### Lab schedule
Labs meet in B21, our lab room in the basement of the Gates building.

- Monday, 1:00pm-3:00pm
- Wednesday,11:30am-1:30pm

Labs run in a Monday-Wednesday sequence, where Monday is exposed to the new lab first, and Wednesday does the same lab. Assignments will be assigned after Monday lab, and due before Wednesday lab of the next week.

*NOTE: We changed the initial Friday-Monday labs to Monday-Wednesday labs. So the Friday lab has been converted to Wednesday.

### Common questions about lab
---

*Written by Julie Zelenski, modified for CS107E by Pat Hanrahan*

**What is a lab?**

Each student **must** participate in a weekly 2-hour lab section 
that focuses on active hands-on experimentation and practical skill-building.
In lab, you will work on a set of exercises/tasks that reinforce 
the week's material.
When you leave the lab, you should be well-prepared
to do the assignment for that week.
Instructors and CAs will be available during the labs.

The labs will often involve hardware.
For example, in the first lab you will learn 
how to create a circuit on a breadboard.
We will bring tools and supplies to the labs. 

**How is lab credit awarded?**

Labs are graded for participation on a credit/no-credit basis.
To earn credit,
you need to arrive on-time and actively participate for the full lab period.
We are hopeful the lab period will be enough time to work through all exercises,
but what you don't finish, we encourage you to complete on your own.

During the lab, we ask that you periodically check-in with the course staff, so we can see how you're doing and help resolve any issues that come up. This check-in also serves as our way of tracking your participation.


**What is the lab collaboration policy?**

More heads are better than one for this kind of experimenting,
so you will work in **pairs.** 
You are also encouraged to discuss the work 
and share ideas with others in your lab room.
Lab time is for active, hands-on, collaborative learning 
-- please offer your help to your peers 
and seek advice from your peers and the staff.
The goal is for everyone to come away 
with a clear understanding of the lab concepts 
and be prepared to go on to complete the assignments 
(which are done individually).

**Is it okay to arrive to lab late or leave early?**

We award credit for labs based on participation and effort.
We expect you to arrive on-time and participate for the full lab period 
(or until satisfactorily completing all lab exercises).
We won't quibble about few minutes here or there but beyond that,
arriving late or skipping out early will result in not receiving lab credit.

**What happens if I miss my lab?**

If you do have to miss attending your lab session one week, 
please come to the other session if possible. If you 
miss a lab entirely,
you must still complete the exercises on your own.

Many of the labs go over material for that week's assignment. 
If you skip a lab, you may have trouble doing the assignment.

