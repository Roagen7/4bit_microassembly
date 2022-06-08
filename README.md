# 4 bit microassembly


## DESCRIPTION

emulation of a 4 bit programmable data bus  



## REFERENCE

### REGISTERS:

Three general purpose registers RA, RB, RC.  
Two helper registers R1, R2.  
Instruction register RI.  
Output register RO.  


Transmitter codes

        C   B   A
    x   0   0   0
    RA  0   0   1
    RB  0   1   0
    ALU 0   1   1
    RC  1   0   0
    DAT 1   0   1

Receiver codes

        C   B   A
    RI  0   0   0
    RA  0   0   1
    RB  0   1   0
    R1  0   1   1
    RC  1   0   0
    RO  1   0   1
    R2  1   1   0

### INSTRUCTIONS:

each cycle consists of 4 microcycles (KK):

00, 01, 10, 11

each microcycle consists of 8 bits

    C B A C B A V1 V2

first CBA triplet is responsible for the choice of transmitter  
second CBA triplet is responsible for the choice of receiver  
V1 V2 are for ALU programming

ram can store up to 8 instructions:

000, 001, 010, 011, 100, 101, 110, 111

### ALU:

ALU must be programmed through V1 and V2 bits of each cycle

given the cycle

    K K C B A C B A     V   V
    0 0 x x x x x x     M   S3
    0 1 x x x x x x     S2  S1
    1 0 x x x x x x     S0  x
    1 1 x x x x x x     x   x

x means whatever


by setting the M bit, as well as S3 S2 S1 S0 we  
give proper orders to ALU


here is the lookup table with operations depending on the code

                    arithmetic logic
    S3  S2  S1  S0      M=0     M=1
    0   0   0   0       0       \R1
    0   0   0   1     R1+R2   \(R1*R2)
    0   0   1   0    R1*R2-1
    0   0   1   1     R1/R2
    0   1   0   0
    0   1   0   1
    0   1   1   0
    0   1   1   1
    1   0   0   0
    1   0   0   1
    1   0   1   0
    1   0   1   1
    1   1   0   0
    1   1   0   1
    1   1   1   0
    1   1   1   1


### RAM: 


ram can store up to 8 * 4 instructions (8 cycles, 4 microcycles each)
plus information on the order of instructions 


### EXAMPLES

