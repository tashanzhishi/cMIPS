//
// Created by wyb on 15-11-16.
//

#ifndef CMIPS_REGISTER_H
#define CMIPS_REGISTER_H

#define	R_ZERO  0x00
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
#define PC      0x20
#define HI      0x21
#define LO      0x22

#define REG_SIZE 35
#define MEM_SIZE 1024
#define INSTRUCTION_SIZE 50

extern const int INT_MAX;
extern const int INT_MIN;

extern int REG[REG_SIZE]; // 32+3 register
extern unsigned char MEM[MEM_SIZE]; //1KB

extern const char* kRegisterSet[REG_SIZE]; //register set, have 32 and 3 more

#endif //CMIPS_REGISTER_H
