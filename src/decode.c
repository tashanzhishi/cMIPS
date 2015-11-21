//
// Created by wyb on 15-11-19.
//
#include <stdio.h>
#include "decode.h"
#include "util.h"
#include "instruction.h"
#include "register.h"

void DecodeAndExecute()
{
    char buf[80]; //read file line
    //FILE* fp_read = fopen("compile.two","rb");
    //while(fgets(buf,20,fp_read))
    int i=0;
    int instruction_num=MEM_W(CODE_BEGIN);
    REG[PC] = CODE_BEGIN+4;
    printf("\n****compiler****\n");
    for(i=0; i<instruction_num; i++)
    {
        //unsigned int un_int = String2Int(buf);
        int un_int = MEM_W(REG[PC]);
        printf("%d\n",un_int);
        Instruction32 binary32 = *(Instruction32 *)(&un_int);

        unsigned int op=binary32.R.op, rs=binary32.R.rs, rt=binary32.R.rt, \
                rd=binary32.R.rd, sa=binary32.R.sa, func=binary32.R.func, address=binary32.J.address;
        int immetiate=binary32.I.immetiate;

        switch (op) {
            case 0:
                switch (func){
                    case 32:
                        ADD(rd, rs, rt);
                        break;
                    case 33:
                        ADDU(rd, rs, rt);
                        break;
                    case 34:
                        SUB(rd, rs, rt);
                        break;
                    default:
                        printf("decode: op=0 and func error!\n");
                        break;
                }
                break;
            default:
                printf("decode: op error!\n");
                break;
        }
    }
    //fclose(fp_read);
}