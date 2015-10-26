//
// Created by wyb on 15-11-15.
//
#ifndef CMIPS_REGISTER_H
#define CMIPS_REGISTER_H

#define	R_ZERO		0x00
#define	R_AT		0x01
#define	R_V0		0x02
#define	R_V1		0x03
#define	R_A0		0x04
#define	R_A1		0x05
#define	R_A2		0x06
#define	R_A3		0x07
#define	R_T0		0x08
#define	R_T1		0x09
#define	R_T2		0x0a
#define	R_T3		0x0b
#define	R_T4		0x0c
#define	R_T5		0x0d
#define	R_T6		0x0e
#define	R_T7		0x0f
#define	R_S0		0x10
#define	R_S1		0x11
#define	R_S2		0x12
#define	R_S3		0x13
#define	R_S4		0x14
#define	R_S5		0x15
#define	R_S6		0x16
#define	R_S7		0x17
#define	R_T8		0x18
#define	R_T9		0x19
#define	R_K0		0x1a
#define	R_K1		0x1b
#define	R_GP		0x1c
#define	R_SP		0x1d
#define	R_FP		0x1e
#define	R_RA		0x1f
#define PC          0x20
#define HI          0x21
#define LO          0x22

#define REG_SIZE 32
#define MEM_SIZE 1024


#define MEM_B(addr) (MEM[addr])
#define MEM_H(addr) (*(short*)(MEM+addr))
#define MEM_W(addr) (*(int*)(MEM+addr))

extern void LB (const int rt, const int base, const int offset);
extern void LH (const int rt, const int base, const int offset);
extern void LW (const int rt, const int base, const int offset);
extern void SB (const int base, const int offset, const int rt);
extern void SH (const int base, const int offset, const int rt);
extern void SW (const int base, const int offset, const int rt);

extern void ADD (const int rd, const int rs, const int rt);
extern void ADDU (const int rd, const int rs, const int rt);
extern void ADDI (const int rt, const int rs, const int immediate);
extern void ADDIU (const int rt, const int rs, const int immediate);
extern void SUB (const int rd, const int rs, const int rt);
extern void MUL (const int rd, const int rs, const int rt);
extern void MULT (const int rs, const int rt);
extern void DIV (const int rs, const int rt);

extern void AND (const int rd, const int rs, const int rt);
extern void ANDI (const int rt, const int rs, const int immediate);
extern void OR (const int rd, const int rs, const int rt);
extern void ORI (const int rt, const int rs, const int immediate);
extern void XOR (const int rd, const int rs, const int rt);
extern void XORI (const int rt, const int rs, const int immediate);
extern void NOR (const int rd, const int rs, const int rt);

extern void SLL (const int rd, const int rt, const int sa);


#endif //CMIPS_REGISTER_H