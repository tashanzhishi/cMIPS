//
// Created by wyb on 15-11-15.
//

#include<stdio.h>
#include<assert.h>
#include "instruction.h"
#include "register.h"
#include "util.h"

void NOP()
{
    PLUS_PC(4);
}

//mov instruction
//To conditionally move a GPR after testing a GPR value
//if rt != 0 then rd <- rs
void MOVN (const int rd, const int rs, const int rt)
{
    if(REG[rt]!=0)
        REG[rd] = REG[rs];
    PLUS_PC(4);
}
//To conditionally move a GPR after testing a GPR value
//if rt != 0 then rd <- rs
void MOVZ (const int rd, const int rs, const int rt)
{
    if(REG[rt]==0)
        REG[rd] = REG[rs];
    PLUS_PC(4);
}
//Move From HI Register
void MFHI (const int rd)
{
    REG[rd] = REG[HI];
    PLUS_PC(4);
}
//Move From HI Register
void MFLO (const int rd)
{
    REG[rd] = REG[LO];
    PLUS_PC(4);
}

// **************************//
// Load Store instruction   *//
// **************************//
void LB (const int rt, const int base, const int offset)
{
    REG[rt]=(int)MEM_B(REG[base]+offset);
    PLUS_PC(4);
}
void LH (const int rt, const int base, const int offset)
{
    REG[rt]=(int)MEM_H(REG[base]+offset);
    PLUS_PC(4);
}
void LW (const int rt, const int base, const int offset)
{
    REG[rt]=(int)MEM_W(REG[base]+offset);
    PLUS_PC(4);
}
void SB (const int rt, const int base, const int offset)
{
    MEM_B(REG[base]+offset)=(unsigned char)REG[rt];
    PLUS_PC(4);
}
void SH (const int rt, const int base, const int offset)
{
    MEM_H(REG[base]+offset)=(short)REG[rt];
    PLUS_PC(4);
}
void SW (const int rt, const int base, const int offset)
{
    MEM_W(REG[base]+offset)=REG[rt];
    PLUS_PC(4);
}

// **************************//
// arithmetic instruction   *//
// **************************//

//To add 32-bit integers. If an overflow occurs, then trap.
//rd <- rs + rt
void ADD (const int rd, const int rs, const int rt)
{
    assert ( !((REG[rs]>0 && REG[rt]>0 && REG[rt]>INT_MAX-REG[rs]) ||	\
  		     (REG[rs]<0 && REG[rt]<0 && REG[rt]<-1*INT_MIN-REG[rs])) );
    REG[rd] = REG[rs] + REG[rt];
    PLUS_PC(4);
}
//To add 32-bit integers.
//rd <- rs + rt
void ADDU (const int rd, const int rs, const int rt)
{
    REG[rd] = (UINT)REG[rs] + (UINT)REG[rt];
    PLUS_PC(4);
}
//To add a constant to a 32-bit integer. If overflow occurs, then trap.
//rt <- rs + immediate
void ADDI (const int rt, const int rs, const int immediate)
{
    assert ( !((REG[rs]>0 && immediate>0 && REG[rs]>INT_MAX-immediate) ||	\
  		     (REG[rs]<0 && immediate<0 && REG[rs]<-1*INT_MIN-immediate)) );
    REG[rt] = REG[rs] + immediate;
    PLUS_PC(4);
}
//To add a constant to a 32-bit integer.
//rt <- rs + immediate
void ADDIU (const int rt, const int rs, const UINT immediate)
{
    REG[rt] = (UINT)REG[rs] + immediate;
    PLUS_PC(4);
}
//To subtract 32-bit integers. If overflow occurs, then trap
//rd <- rs - rt
void SUB (const int rd, const int rs, const int rt)
{
    assert ( !((REG[rs]>0 && REG[rt]<0 && REG[rs]>INT_MAX+REG[rt]) ||	\
  		     (REG[rs]<0 && REG[rt]>0 && REG[rs]<-1*INT_MIN+REG[rt])) );
    REG[rd] = REG[rs] - REG[rt];
    PLUS_PC(4);
}
//To subtract 32-bit integers
//rd <- rs - rt
void SUBU (const int rd, const int rs, const int rt)
{
    REG[rd] = (UINT)REG[rs] - (UINT)REG[rt];
    PLUS_PC(4);
}
//To multiply two words and write the result to a GPR.
//rd <- rs * rt
void MUL (const int rd, const int rs, const int rt)
{
    REG[rd] = REG[rs] * REG[rt];
    PLUS_PC(4);
}
//To multiply 32-bit signed integers
//(LO, HI) <- rs × rt
void MULT (const int rs, const int rt)
{
    long long temp = (long long)REG[rs] * (long long)REG[rt];
    REG[LO] = (int)temp;
    REG[HI] = (int)(temp>>32);
    PLUS_PC(4);
}
//To multiply 32-bit unsigned integers
//(LO, HI) <- rs × rt
void MULTU (const int rs, const int rt)
{
    unsigned long long temp = (unsigned long long)((UINT)REG[rs] * (UINT)REG[rt]);
    REG[LO] = (UINT)temp;
    REG[HI] = (UINT)(temp>>32);
    PLUS_PC(4);
}
//To divide a 32-bit signed integers
//(LO, HI) <- rs / rt
void DIV (const int rs, const int rt)
{
    REG[LO] = REG[rs] / REG[rt];
    REG[HI] = REG[rs] % REG[rt];
    PLUS_PC(4);
}
//(LO, HI) <- rs / rt
void DIVU (const int rs, const int rt)
{
    REG[LO] = (UINT)REG[rs] / (UINT)REG[rt];
    REG[HI] = (UINT)REG[rs] % (UINT)REG[rt];
    PLUS_PC(4);
}
//Set on Less Than
//To record the result of a less-than comparison
//rd <- (rs < rt)
void SLT (const int rd, const int rs, const int rt)
{
    REG[rd] = (REG[rs] < REG[rt]? 1: 0);
    PLUS_PC(4);
}
//rd <- (rs < rt)
void SLTU (const int rd, const int rs, const int rt)
{
    REG[rd] = (REG[rs] < REG[rt]? 1: 0);
    PLUS_PC(4);
}
//rd <- (rs < immediate)
void SLTI (const int rt, const int rs, const int immediate)
{
    REG[rt] = (REG[rs] < immediate? 1: 0);
    PLUS_PC(4);
}
//rd <- (rs < immediate)
void SLTIU (const int rt, const int rs, const UINT immediate)
{
    REG[rt] = (REG[rs] < (int)immediate? 1: 0);
    PLUS_PC(4);
}


// **************************//
// logic instruction        *//
// **************************//

//To do a bitwise logical AND
//rd <- rs AND rt
void AND (const int rd, const int rs, const int rt)
{
    REG[rd] = REG[rs] & REG[rt];
    PLUS_PC(4);
}
//To do a bitwise logical AND with a constant
//rt <- rs AND immediate
void ANDI (const int rt, const int rs, const int immediate)
{
    REG[rt] = REG[rs] & immediate;
    PLUS_PC(4);
}
//To do a bitwise logical OR
//rd <- rs OR rt
void OR (const int rd, const int rs, const int rt)
{
    REG[rd] = REG[rs] | REG[rt];
    PLUS_PC(4);
}
//To do a bitwise logical OR with a constant
//rt <- rs OR immediate
void ORI (const int rt, const int rs, const int immediate)
{
    REG[rt] = REG[rs] | immediate;
    PLUS_PC(4);
}
//To do a bitwise logical Exclusive OR
//rd <- rs XOR rt
void XOR (const int rd, const int rs, const int rt)
{
    REG[rd] = REG[rs] ^ REG[rt];
    PLUS_PC(4);
}
//To do a bitwise logical Exclusive OR with a constant
//rt <- rs XOR immediate
void XORI (const int rt, const int rs, const int immediate)
{
    REG[rt] = REG[rs] ^ immediate;
    PLUS_PC(4);
}
//To do a bitwise logical NOT OR
//rd <- rs NOR rt
void NOR (const int rd, const int rs, const int rt)
{
    REG[rd] = ~(REG[rs] | REG[rt]);
    PLUS_PC(4);
}
//To load a constant into the upper half of a word
//Load Upper Immediate
//rt <- immediate << 16
void LUI (const int rt, const int immediate)
{
    REG[rt] = (immediate << 16);
    PLUS_PC(4);
}

// **************************//
// logical shift instruction //
// **************************//

//Shift Word Left Logical
//To left-shift a word by a fixed number of bits
//rd <- rt << sa
void SLL (const int rd, const int rt, const UINT sa)
{
    REG[rd] = (REG[rt] << sa);
    PLUS_PC(4);
}
//Shift Word Left Logical Variable
//rd <- rt << rs[4-0]
void SLLV (const int rd, const int rt, const int rs)
{
    REG[rd] = (REG[rt] << (REG[rs] & 0x0000001f));
    PLUS_PC(4);
}
//Shift Word Right Arithmetic
//rd <- rt >> sa
void SRA (const int rd, const int rt, const UINT sa)
{
    REG[rd] = (REG[rt] >> sa);
    PLUS_PC(4);
}
//Shift Word Right Arithmetic Variable
//rd <- rt >> rs[4-0]
void SRAV (const int rd, const int rt, const int rs)
{
    REG[rd] = (REG[rt] >> (REG[rs] & 0x0000001f));
    PLUS_PC(4);
}
//Shift Word Right Logical
//rd <- rt >> sa
void SRL (const int rd, const int rt, const UINT sa)
{
    REG[rd] = ((UINT)REG[rt] >> sa);
    PLUS_PC(4);
}
//Shift Word Right Logical Variable
//rd <- rt >> rs[4-0]
void SRLV (const int rd, const int rt, const int rs)
{
    REG[rd] = ((UINT)REG[rt] >> ((UINT)REG[rs] & 0x0000001f));
    PLUS_PC(4);
}

// *****************************//
// Branch and Jump Instructions //
// *****************************//

//To branch within the current 256 MB-aligned region
//J target
void J (const UINT target)
{
    REG[PC] = REG[PC] + 4;
    REG[PC] = (REG[PC] & 0xf0000000) | (target << 2);
}
//To execute a procedure call within the current 256 MB-aligned region
//JAL target
void JAL (const UINT target)
{
    REG[R_RA] = REG[PC] + 8;
    REG[PC] = (REG[PC] & 0xf0000000) | (target << 2);
}
//Branch on Less Than Zero
//if rs < 0 then branch
void BLTZ (const int rs, const int offset)
{
    if (REG[rs] < 0)
        REG[PC] += (offset << 2);
}
//Branch on Less Than or Equal to Zero
//if rs <= 0 then branch
void BLEZ (const int rs, const int offset)
{
    if (REG[rs] <= 0)
        REG[PC] += (offset << 2);
}
//Branch on Greater Than Zero
//if rs > 0 then branch
void BGTZ (const int rs, const int offset)
{
    if (REG[rs] > 0)
        REG[PC] += (offset << 2);
}
//Branch on Greater Than or Equal to Zero
//if rs >= 0 then branch
void BGEZ (const int rs, const int offset)
{
    if (REG[rs] >= 0)
        REG[PC] += (offset << 2);
}
//Branch on Equal
//if rs = rt then branch
void BEQ (const int rs, const int rt, const int offset)
{
    if(REG[rs] == REG[rt])
        REG[PC] += (offset << 2);
}
//Branch on Not Equal
//if rs != rt then branch
void BNE (const int rs, const int rt, const int offset)
{
    if(REG[rs] != REG[rt])
        REG[PC] += (offset << 2);
}
