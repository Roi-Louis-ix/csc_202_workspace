.global my_asm_16bitset
.global my_asm_16bitclr
.global my_asm_16bitcheck

my_asm_16bitset:
    ORRS R0, R0, R1 //R0 = R0 | R1
    BX LR //Back to the calling function

my_asm_16bitclr:
    BICS R0, R0, R1 //R0 = R0 & ~R1
    BX LR

my_asm_16bitcheck:
    ANDS R0, R0, R1 //R0 = R0 & R1
    CMP R0, R1 //Test if R0 = R1
    BEQ SAME //If R0 = R1 jump to SAME
    MOVS R0, #0 //Output R0 = 0
    BX LR

SAME:
    MOVS R0, #1 //Output R0 = 1
    BX LR

    