This program allows for experimentation of the evolution of complexity through the development of logic tasks of 
increasing difficulty by digital organisms in a 60 x 60 grid. The organisms are rewarded points on every update, and
can use these points to reproduce. Performing more complex tasks rewards organisms with more points, so organisms
that can successfully carry out difficult tasks will proliferate their genomes and are more likely to produce offspring
that can do the same as them. There is also a mutation element that allows random chance to play a part in this
process of digital evolution.

There exist nine logic tasks, listed in ascending complexity:

NOT
NAND
AND
ORN
OR
ANDN
NOR
XOR
EQU

Which are implemented in the Task.h file. 

This program uses SGPLite, which is built on top of the Empirical library and allows for smooth implementation of digital organisms that can evolve new 'traits' of increasing complexity.

The program can be run both on the native and web files. The native file allows for quicker execution which is more advantageous for data collection. The web file allows for visualization of the system which provides a better understanding of the way the evolution is occurring in the world. 
