//
// Created by wyb on 15-11-15.
//

#ifndef CMIPS_COMPILER_H
#define CMIPS_COMPILER_H

#define PARAMETERS_NUM 4 //the max number of parameters in a instruction
#define PARAMETER_LENGTH 50 //the length of a parameter
#define INSTRUCTION_KIND 7 //the kind of instruction, as follow

#define OP_NAME 1
#define OP_REG 2
#define OP_REG_REG 3
#define OP_REG_IMM 4
#define OP_REG_REG_REG 5
#define OP_REG_IMM_REG 6
#define OP_REG_REG_IMM 7

extern void CompileMIPS(FILE* fp);
extern unsigned int Instruction2Binary(char (*parameter)[50], const int parameter_num, const int kind_num);

#endif //CMIPS_COMPILER_H
