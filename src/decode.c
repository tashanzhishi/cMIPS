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
    //char buf[80]; //read file line
    //FILE* fp_read = fopen("compile.two","rb");
    //while(fgets(buf,20,fp_read))
    int i=0;
    int program_end_pointer=MEM_W(CODE_BEGIN)*4+4;
    REG[PC] = CODE_BEGIN+4;
    printf("\n****excute****\n");
    while (REG[PC] < program_end_pointer)
    {
        //printf("%d:%d %d %d %d\n",REG[PC],REG[R_SP],REG[R_T0],REG[R_T1],REG[R_T2]);
        //unsigned int un_int = String2Int(buf);
        int un_int = MEM_W(REG[PC]);
        printf("%u\n",un_int);
        Instruction32 binary32 = *(Instruction32 *)(&un_int);

        unsigned int op=binary32.R.op, rs=binary32.R.rs, rt=binary32.R.rt, \
                rd=binary32.R.rd, sa=binary32.R.sa, func=binary32.R.func, address=binary32.J.address;
        int imm=binary32.I.immetiate;

        switch (op) {
            case 0:
                switch (func){
                    case 0:
                        SLL(rd,rt,sa);
                        break;
                    case 2:
                        SRL(rd,rt,sa);
                        break;
                    case 3:
                        SRA(rd,rt,sa);
                        break;
                    case 4:
                        SLLV(rd,rt,sa);
                        break;
                    case 6:
                        SRLV(rd,rt,sa);
                        break;
                    case 7:
                        SRAV(rd,rt,sa);
                        break;
                    case 10:
                        MOVZ(rd,rs,rt);
                        break;
                    case 11:
                        MOVN(rd,rs,rt);
                        break;
                    case 16:
                        MFHI(rd);
                        break;
                    case 18:
                        MFLO(rd);
                        break;
                    case 24:
                        MULT(rs,rt);
                        break;
                    case 25:
                        MULTU(rs,rt);
                        break;
                    case 26:
                        DIV(rs,rt);
                        break;
                    case 27:
                        DIVU(rs,rt);
                        break;
                    case 32:
                        ADD(rd, rs, rt);
                        break;
                    case 33:
                        ADDU(rd, rs, rt);
                        break;
                    case 34:
                        SUB(rd, rs, rt);
                        break;
                    case 35:
                        SUBU(rd,rs,rt);
                        break;
                    case 36:
                        AND(rd,rs,rt);
                        break;
                    case 37:
                        OR(rd,rs,rt);
                        break;
                    case 38:
                        XOR(rd,rs,rt);
                        break;
                    case 39:
                        NOR(rd,rs,rt);
                        break;
                    case 42:
                        SLT(rd,rs,rt);
                        break;
                    case 43:
                        SLTU(rd,rs,rt);
                        break;
                    default:
                        printf("decode: op=0 and func error!\n");
                        break;
                }
                break;
            case 1:
                switch (rt){
                    case 0:
                        BLTZ(rs,imm);
                        break;
                    case 1:
                        BGEZ(rs,imm);
                        break;
                    default:
                        printf("decode: op=1 and rt error!\n");
                        break;
                }
                break;
            case 2:
                J(address);
                break;
            case 3:
                JAL(address);
                break;
            case 4:
                BEQ(rs,rt,imm);
                break;
            case 5:
                BNE(rs,rt,imm);
                break;
            case 6:
                BLEZ(rs,imm);
                break;
            case 7:
                BGTZ(rs,imm);
                break;
            case 8:
                ADDI(rt,rs,imm);
                break;
            case 9:
                ADDIU(rt,rs,imm);
                break;
            case 10:
                SLTI(rt,rs,imm);
                break;
            case 11:
                SLTIU(rt,rs,imm);
                break;
            case 12:
                ANDI(rt,rs,imm);
                break;
            case 13:
                ORI(rt,rs,imm);
                break;
            case 14:
                XORI(rt,rs,imm);
                break;
            case 15:
                LUI(rt,imm);
                break;
            case 28:
                switch (func){
                    case 2:
                        MUL(rd,rs,rt);
                        break;
                    default:
                        printf("decode: op=28 and func error\n");
                }
                break;
            case 32:
                LB(rt,rs,imm);
                break;
            case 33:
                LH(rt,rs,imm);
                break;
            case 35:
                LW(rt,rs,imm);
                break;
            case 40:
                SB(rt,rs,imm);
                break;
            case 41:
                SH(rt,rs,imm);
                break;
            case 43:
                SW(rt,rs,imm);
                break;
            default:
                printf("decode: op error!\n");
                break;
        }
    }
    //fclose(fp_read);
}



