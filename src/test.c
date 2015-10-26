//
// Created by wyb on 15-11-15.
//
#include<stdio.h>
#include<string.h>
#include "register.h"

extern unsigned int REG[REG_SIZE+3];
extern unsigned char MEM[MEM_SIZE];

void TestMemory ()
{
    memset (REG,sizeof(REG),0);
    int i=0;
    for (i=0;i<10;i++) MEM[i]=i;
    LB (1,0,3); //REG[1]=3
    LH (2,0,0); //REG[2]=0x100
    LW (3,0,0); //REG[3]=0x03020100
    printf ("0x%08x 0x%08x 0x%08x\n",REG[1],REG[2],REG[3]);

    memset (MEM,sizeof(MEM),0);
    REG[0]=0,REG[1]=0x12,REG[2]=0x1234,REG[3]=0x12345678;
    SB (0,1,1); //MEM[1]=REG[1]低8位
    SH (0,10,2); //MEM[2]=REG[2]低16位
    SW (0,20,3); //MEM[3]=REG[3]低32位
    printf ("0x%08x 0x%08x 0x%08x\n",MEM_B(1),MEM_H(10),MEM_W(20));

    REG[R_S0]=500, REG[R_S1]=200;
    ADD (R_S2,R_S0,R_S1);
    printf ("%d\n",REG[R_S2]);
}
int main ()
{
    TestMemory();
    return 0;
}