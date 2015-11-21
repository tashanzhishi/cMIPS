//
// Created by wyb on 15-11-15.
//
#ifndef CMIPS_INSTRUCTION_H
#define CMIPS_INSTRUCTION_H

#define PLUS_PC(offset) (REG[PC]=REG[PC]+offset)
typedef unsigned int UINT;

extern void NOP();

extern void MOVN (const int rd, const int rs, const int rt);
extern void MOVZ (const int rd, const int rs, const int rt);
extern void MFHI (const int rd);
extern void MFLO (const int rd);

extern void LB (const int rt, const int base, const int offset);
extern void LH (const int rt, const int base, const int offset);
extern void LW (const int rt, const int base, const int offset);
extern void SB (const int rt, const int base, const int offset);
extern void SH (const int rt, const int base, const int offset);
extern void SW (const int rt, const int base, const int offset);

extern void ADD (const int rd, const int rs, const int rt);
extern void ADDU (const int rd, const int rs, const int rt);
extern void ADDI (const int rt, const int rs, const int immediate);
extern void ADDIU (const int rt, const int rs, const UINT immediate);
extern void SUB (const int rd, const int rs, const int rt);
extern void SUBU (const int rd, const int rs, const int rt);
extern void MUL (const int rd, const int rs, const int rt);
extern void MULT (const int rs, const int rt);
extern void MULTU (const int rs, const int rt);
extern void DIV (const int rs, const int rt);
extern void DIVU (const int rs, const int rt);
extern void SLT (const int rd, const int rs, const int rt);
extern void SLTU (const int rd, const int rs, const int rt);
extern void SLTI (const int rt, const int rs, const int immediate);
extern void SLTIU (const int rt, const int rs, const UINT immediate);

extern void AND (const int rd, const int rs, const int rt);
extern void ANDI (const int rt, const int rs, const int immediate);
extern void OR (const int rd, const int rs, const int rt);
extern void ORI (const int rt, const int rs, const int immediate);
extern void XOR (const int rd, const int rs, const int rt);
extern void XORI (const int rt, const int rs, const int immediate);
extern void NOR (const int rd, const int rs, const int rt);
extern void LUI (const int rt, const int immediate);

extern void SLL (const int rd, const int rt, const UINT sa);
extern void SLLV (const int rd, const int rt, const int rs);
extern void SRA (const int rd, const int rt, const UINT sa);
extern void SRAV (const int rd, const int rt, const int rs);
extern void SRL (const int rd, const int rt, const UINT sa);
extern void SRLV (const int rd, const int rt, const int rs);

extern void J (const UINT target);
extern void JAL (const UINT target);
extern void BLTZ (const int rs, const int offset);
extern void BLEZ (const int rs, const int offset);
extern void BGTZ (const int rs, const int offset);
extern void BGEZ (const int rs, const int offset);
extern void BEQ (const int rs, const int rt, const int offset);
extern void BNE (const int rs, const int rt, const int offset);

#endif //CMIPS_INSTRUCTION_H