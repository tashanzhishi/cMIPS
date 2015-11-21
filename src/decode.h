//
// Created by wyb on 15-11-19.
//

#ifndef CMIPS_DECODE_H
#define CMIPS_DECODE_H

//R instruction
typedef struct InstructionOfR {
    unsigned int func:6;
    unsigned int sa:5;
    unsigned int rd:5;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int op:6;
} Instruction_R;

//I instruction
typedef struct InstructionOfI {
    int immetiate:16;
    unsigned int rt:5;
    unsigned int rs:5;
    unsigned int op:6;
} Instruction_I;

//J instruction
typedef struct InstructionOfJ {
    unsigned int address:26;
    unsigned int op:6;
} Instruction_J;

//3 mips32 instruction
typedef union InstructionOfMIPS32 {
    Instruction_R R;
    Instruction_I I;
    Instruction_J J;
} Instruction32;

extern void DecodeAndExecute();

#endif //CMIPS_DECODE_H
