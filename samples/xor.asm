ORIGIN 0xfe00
LDi    2           67
LDi    3           88
ST     2       0xa002
ST     3       0xa003
JMP    1
ORIGIN 1
LDm    0       0xa002
LDm    1       0xa003
ST 0 0xb000
NAND 1
ST 0 0xb001   # anb  0xb001
LDm 0 0xb000
LDm 2 0xb001
NAND 2
ST 0 0xb002  # A nand (A nand B)
LDm 0 0xa003 # B in r0
NAND 2
LDm 2 0xb002
NAND 2
ST 0 0x0000
