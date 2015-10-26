#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"register.h"


unsigned int REG[REG_SIZE+3]={0};// 32+3 register
unsigned char MEM[MEM_SIZE]={0};//1KB
const int INT_MAX = 0x79999999;
const int INT_MIN = 0x80000000;

//memory instruction
void LB (const int rt, const int base, const int offset)
{
  REG[rt]=MEM_B(REG[base]+offset);
}
void LH (const int rt, const int base, const int offset)
{
  REG[rt]=MEM_H(REG[base]+offset);
}
void LW (const int rt, const int base, const int offset)
{
  REG[rt]=MEM_W(REG[base]+offset);
}
void SB (const int base, const int offset, const int rt)
{
  MEM_B(REG[base]+offset)=(char)REG[rt];
}
void SH (const int base, const int offset, const int rt)
{
  MEM_H(REG[base]+offset)=(short)REG[rt];
}
void SW (const int base, const int offset, const int rt)
{
  MEM_W(REG[base]+offset)=(int)REG[rt];
}

//arithmetic instruction
//To add 32-bit integers. If an overflow occurs, then trap.
//rd <- rs + rt
void ADD (const int rd, const int rs, const int rt)
{
  assert ( !((REG[rs]>0 && REG[rt]>0 && REG[rt]>INT_MAX-REG[rs]) ||	\
  		     (REG[rs]<0 && REG[rt]<0 && REG[rt]<-1*INT_MIN-REG[rs])) );
  REG[rd] = REG[rs] + REG[rt];
}
//To add 32-bit integers.
//rd <- rs + rt
void ADDU (const int rd, const int rs, const int rt)
{
  REG[rd] = REG[rs] + REG[rt];
}
//To add a constant to a 32-bit integer. If overflow occurs, then trap.
//rt <- rs + immediate
void ADDI (const int rt, const int rs, const int immediate)
{
  assert ( !((REG[rs]>0 && immediate>0 && REG[rs]>INT_MAX-immediate) ||	\
  		     (REG[rs]<0 && immediate<0 && REG[rs]<-1*INT_MIN-immediate)) );
  REG[rt] = REG[rs] + immediate;
}
//To add a constant to a 32-bit integer.
//rt <- rs + immediate
void ADDIU (const int rt, const int rs, const int immediate)
{
  REG[rt] = REG[rs] + immediate;
}
//To subtract 32-bit integers. If overflow occurs, then trap
//rd <- rs - rt
void SUB (const int rd, const int rs, const int rt)
{
  assert ( !((REG[rs]>0 && REG[rt]<0 && REG[rs]>INT_MAX+REG[rt]) ||	\
  		     (REG[rs]<0 && REG[rt]>0 && REG[rs]<-1*INT_MIN+REG[rt])) );
  REG[rd] = REG[rs] - REG[rt];
}
//To multiply two words and write the result to a GPR.
//rd <- rs * rt
void MUL (const int rd, const int rs, const int rt)
{
  REG[rd] = REG[rs] * REG[rt];
}
//To multiply 32-bit signed integers
//(LO, HI) <- rs × rt
void MULT (const int rs, const int rt)
{
  REG[LO] = REG[rs] * REG[rt];
  REG[HI] = ((REG[rs]*REG[rt])>>32);
}
//To divide a 32-bit signed integers
//(LO, HI) <- rs / rt
void DIV (const int rs, const int rt)
{
  REG[LO] = REG[rs] / REG[rt];
  REG[HI] = REG[rs] % REG[rt];
}

//logic instruction
//To do a bitwise logical AND
//rd <- rs AND rt
void AND (const int rd, const int rs, const int rt)
{
  REG[rd] = REG[rs] & REG[rt];
}
//To do a bitwise logical AND with a constant
//rt <- rs AND immediate
void ANDI (const int rt, const int rs, const int immediate)
{
  REG[rt] = REG[rs] & immediate;
}
//To do a bitwise logical OR
//rd <- rs OR rt
void OR (const int rd, const int rs, const int rt)
{
  REG[rd] = REG[rs] | REG[rt];
}
//To do a bitwise logical OR with a constant
//rt <- rs OR immediate
void ORI (const int rt, const int rs, const int immediate)
{
  REG[rt] = REG[rs] | immediate;
}
//To do a bitwise logical Exclusive OR
//rd <- rs XOR rt
void XOR (const int rd, const int rs, const int rt)
{
  REG[rd] = REG[rs] ^ REG[rt];
}
//To do a bitwise logical Exclusive OR with a constant
//rt <- rs XOR immediate
void XORI (const int rt, const int rs, const int immediate)
{
  REG[rt] = REG[rs] ^ immediate;
}
//To do a bitwise logical NOT OR
//rd <- rs NOR rt
void NOR (const int rd, const int rs, const int rt)
{
  REG[rd] = ~(REG[rs] | REG[rt]);
}

//logical shift instruction
//To left-shift a word by a fixed number of bits
//rd <- rt << sa
void SLL (const int rd, const int rt, const int sa)
{
  REG[rd] = (REG[rt] << sa);
}






