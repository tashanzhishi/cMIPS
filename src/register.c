#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"register.h"

#define REG_SIZE 32
#define MEM_SIZE 1024
const int INT_MAX = 0x79999999;
const int INT_MIN = 0x80000000;
unsigned int REG[REG_SIZE]={0};// 32 register
unsigned char MEM[MEM_SIZE]={0};//1KB

void test ()
{
  memset (REG,sizeof(REG),0);
  int i=0;
  for (i=0;i<10;i++) MEM[i]=i;
  LB (0,1,3); //REG[1]=3
  LH (0,2,0); //REG[2]=0x100
  LW (0,3,0); //REG[3]=0x03020100
  printf ("%08x %08x %08x\n",REG[1],REG[2],REG[3]);
  
  memset (MEM,sizeof(MEM),0);
  REG[1]=0x12,REG[2]=0x1234,REG[3]=0x12345678;
  SB (0,1,1); //MEM[1]=REG[1]低8位
  SH (0,2,2); //MEM[2]=REG[2]低16位
  SW (0,3,3); //MEM[3]=REG[3]低32位
  printf ("%x %x %x\n",MEM[1],MEM[2],MEM[3]);

  REG[R_S0]=INT_MAX, REG[R_S1]=200;
  ADD (R_S2,R_S0,R_S1);
  printf ("%d\n",REG[R_S2]);
}
int main ()
{
  test();
  return 0;
}

void LB (int base, int rt, int offset)
{
  REG[rt]=MEM_B(REG[base]+offset);
}
void LH (int base, int rt, int offset)
{
  REG[rt]=MEM_H(REG[base]+offset);
}
void LW (int base, int rt, int offset)
{
  REG[rt]=MEM_W(REG[base]+offset);
}
void SB (int base, int rt, int offset)
{
  MEM_B(REG[base]+offset)=(char)REG[rt];
}
void SH (int base, int rt, int offset)
{
  MEM_H(REG[base]+offset)=(short)REG[rt];
}
void SW (int base, int rt, int offset)
{
  MEM_W(REG[base]+offset)=(int)REG[rt];
}
void ADD (int rd, int rs, int rt)
{
  assert ( !(REG[rs]>0 && REG[rt]>INT_MAX-REG[rs])||	\
  		    (REG[rs]<0 && REG[rt]<INT_MIN-REG[rs]) );
  REG[rd] = REG[rs] + REG[rt];
}
