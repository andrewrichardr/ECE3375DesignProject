# ECE3375DesignProject
Repo for the ECE3375B Design Project
Design Assignment – Thinking about an embedded system
This design exercise has been developed to give you a chance to go through the steps of an embedded
design. Given our limits on resources and time, we will limit implementation to software prototyping.
This work is to be completed in groups of at least two and at most four. Ideally, I would like you to
form groups of an interdisciplinary nature. There are some parts of the work that are more natural for
people who prefer software, and some parts that are more natural for people who prefer hardware.
Embedded development often brings such people together in groups. However, I will not insist.
Deliverables:
My expectations for the assignment are as follows:
1. Progress Report: Due March 11. The progress report should contain problem definition,
functional description, I/O requirements, initial software design and prototyping plan. See
below for definitions of each of these components.
2. Lab attendance: Between March 26-April 4. Each lab section has one three-hour lab session set
aside for design prototype testing.
3. Lab demo: April 8 and April 9. Each group should send one representative to a selected lab
section in the first week of April to demo the work.
4. Final Report: Due April 9. 

The final report should contain microcontroller selection, revised
software design, results from prototyping, source code, lessons learned. See below for
definitions of each of these components.
IMPORTANT NOTE: One point I would like to make ABSOLUTELY CLEAR at the outset. This is a project in
embedded software design and implementation. It is NOT about making mechatronic systems. Of course
if you want to make some kind of electromechanical widget with moving parts, you can do so, but there
are NO MARKS associated with such effort.
Step 1: Problem definition
My objective with this assignment is to give you a chance to design “something”. I really do not care what,
as long as it is an engineered system with embedded intelligence. The nature of the world we live in is
such that almost every engineered system can make use of embedded computing in some way, so you
have a lot of freedom here. In order to help you come up with some ideas, I present the following list of
projects that fourth-year students have worked on under my supervision in recent years. I DO NOT intend
this list to be exhaustive, and I DO NOT intend for you to choose from it, though you can if you want to.

• Wearable system to detect local “wind chill” factor while skiing

• System to set the shower temperature and pressure automatically for a given user

• RFID-based door lock/light switch

• Automated system to turn on and off room lights based on occupancy

• Motor controller for electric bicycle

• Home thermostat with multiple, remotely located temperature sensors

• System to lock out the stall and alert the custodial staff when the toilet paper runs out

Deliverable: Describe the problem and provide the specifications to be met by the embedded system.

Step 2: Functional description
For many of you, this will come at the same time as problem definition, but it important to make sure it
gets done. My objective here is for you to answer questions like the following:

• What does the system do?
• How does a user interact with it?
• What other devices (if any) does it interact with? How does that happen?
• What quantities does it monitor? How often?
• What stimuli does it manage? How often?

Essentially, try to imagine your finished system as a “black box”. How would you describe what is inside
it?

Deliverable: A functional description can be mostly written or mostly diagrams
Step 2: Identify I/O requirements

Once you have identified a problem and you understand its functional requirements, you will need to
determine what inputs and outputs you require. Inputs may take the form of analog values, digital values,
user inputs, communication inputs and so on. Outputs may take the form of analog outputs, digital
outputs, PWM outputs, communication outputs and so on. It is difficult to provide guidance in this area,
because the range of possible applications is so broad. Basically, we proceed as follows:
First, determine what you have to measure, and what you have to do. This can be left in the application
domain (ie: “If the water is too hot, I need to cool it down”).
Second, identify what transducers (sensors and actuators) can be used to accomplish this objective. In
many cases, all you need is google. You will find that in almost all cases, no matter what you want to
measure or control, you have a choice between buying a simple transducer that requires you to do much
of the wiring, signal conditioning and calibration OR a digital system that already contains most of the
wiring but requires you to understand some kind of communication protocol.
Deliverable: Identify your inputs and outputs. Include in your discussion what tools or circuits you will
need to interface to the transducers.

Step 3: Initial software design
Okay, you have a problem, you have electronics. You don’t have a microcontroller selected yet, but you
will have one and you know what they are. So all you need now is software. Provide a document
outlining how the software will be designed. As usual, I don’t care what format it takes (don’t waste time
drawing me UML diagrams). You may want to address the following questions:
1) What initialization does your software need to perform?
2) How are your various inputs sampled? How is the data communicated to the rest of the software?
3) How are your various outputs computed?
4) What does your software spend most of its time doing? Can it run forever?
5) How do the various components of your software (input processing, output processing,
computation) interact?
Deliverable: A software design document that addresses the questions above (and whatever else you
would like to tell me).

Step 4: Prototyping plan
Embedded systems developers in the real world have a common problem. The hardware is always late.
Too often, this means waiting until the hardware is finished before you begin any kind of software testing.
That leads to angry customers and failed projects.
One possible solution is software prototyping. Basically, this means “faking out” the presence of the
hardware, to see if the software behaves properly.
What I would like you to do in this project is implement some pieces of your designed software that you
can test using the tools we have available in the lab. We have the ability to present both analog and digital
inputs to our ARM platforms, and we have the ability to monitor digital and timed outputs. With a little
warning, we can make simple communications available as well.
Deliverable: In your prototyping plan, pick the pieces of your software design that you would like to get
working in the lab. What tests would you like to run? How will you verify success?

Step 5: Select your microcontroller
In our class, we have focused on the ARM. However, the ARM is not the only microcontroller in the
world. For this section, I would like you to find at least one other microcontroller (you may want to
investigate the Texas Instruments MSP430 family, for example, which is very versatile) and compare the
two of them. Outline how you might decide which one to use for your application.
Note that for final implementation, you DO NOT have to work on the DE10 if you have a preferred
platform, but you DO have to work “on the bare metal”. This means NO Arduino, NO Raspberry PI, NO
any other system that provides a runtime environment.
Deliverable: Provide a discussion outlining how you made your decision

Step 6: Revised software design
No plan survives contact with the enemy. Now we are at the end of the course, can you revise your
software design? What has changed as you learned and worked with the ARM? In particular, can you see
a role for interrupts in your design, now that you know what they do?
Deliverable: A software design document that addresses the questions above (and whatever else you
would like to tell me).

Step 7: Results from prototyping
Tell us how it went. Were you able to get any pieces working in the lab? What is the next step?
Deliverable: Report on the lab experience AND provide a debug/test plan for when the hardware is
ready.

Step 8: Source code
Deliverable: Submit what you have.

Step 9: Lessons learned
I would like you to reflect on the experience of the course labs as a whole. Have you learned anything?
Did this project help pull together how the various pieces of this course fit together? Do you see how you
can integrated microcontroller technology into future projects?
