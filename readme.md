# CPU

#### This repository allows you to simulate the operation of a processor that works on data structures - a stack.

##### 1) To get started with the processor, download the repository compile the asm in the ASM folder and the cpu in the CPU folder
##### 2) Go to the ASM folder.
##### 3) Use commands:
*IN* - enter the value from keyboard\
*PUSH* - push value in cpu's stack\
*OUT* - show the top element of stack\
*ADD* - addition\
*SUB* - subtraction\
*MUL* - multiplication\
*DIV* - division\
*POP* - take the top element\
*JMP* - for jump\
**:**"name of label" - set label\
**:** *call* - call function\
*HLT* - finish programm\
##### for examples of using all commands, see the examples in the examples folder
##### 4) Run asm "name of sourse file"
##### 5) In the CPU folder, run the cpu file
##### 6) If something is not working properly, look at logs in the LOGS folder.


### Example
#### ASM code:              
>PUSH 5\
PUSH 4\
MUL\
OUT\
HLT\
#### Output
>20
