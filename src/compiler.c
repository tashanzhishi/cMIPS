//
// Created by wyb on 15-11-15.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "compiler.h"
#include "util.h"
#include "register.h"

void CompileMIPS()
{
    //7 regex expressions
    const char* op_name = "(\\w+)\\s+(\\w+)\\s*";
    const char* op_reg = "(\\w+)\\s+\\$(\\w+)\\s*";
    const char* op_reg_reg = "(\\w+)\\s+\\$(\\w+)\\s*,\\s*\\$(\\w+)\\s*";
    const char* op_reg_imm = "(\\w+)\\s+\\$(\\w+)\\s*,\\s*(#[0-9]+)\\s*";
    const char* op_reg_reg_reg = "(\\w+)\\s+\\$(\\w+)\\s*,\\s*\\$(\\w+)\\s*,\\s*\\$(\\w+)\\s*";
    const char* op_reg_imm_reg = "(\\w+)\\s+\\$(\\w+)\\s*,\\s*([0-9]+)\\(\\$(\\w+)\\)";
    const char* op_reg_reg_imm = "(\\w+)\\s+\\$(\\w+)\\s*,\\s*\\$(\\w+)\\s*,\\s*\\#([0-9]+)";
    char pattern[1000];
    sprintf(pattern,"%s|%s|%s|%s|%s|%s|%s",op_name,op_reg,op_reg_reg,op_reg_imm,op_reg_reg_reg,op_reg_imm_reg,op_reg_reg_imm);
    //sprintf(pattern,"%s|%s",op_loop,op_reg);
    //printf("%s\n",pattern);
    const int op_kind[INSTRUCTION_KIND]={1,3,5,8,11,15,19};

    regex_t reg;
    regcomp(&reg, pattern, REG_EXTENDED|REG_NEWLINE);
    int status;
    regmatch_t pmatch[23]; //23 groups, which is "()" number of regex
    const int nmatch = 23;

    char buf[80]; //read file line
    FILE* fp_read = fopen("program.mips","rb");
    //FILE* fp_write = fopen("compile.two","wb");
    if(fp_read==NULL)
        printf("fopen error\n");

    //save the mips parameter,there are 5 most. [add $t1,$t2,$t3],[add],[$t1],[$t2],[$t3]
    char parameter[PARAMETERS_NUM+1][PARAMETER_LENGTH];
    int parameter_num=0, kind_num=-1, program_pr=CODE_BEGIN+4, instruction_num=0;

    printf("\n****code****\n");

    while(fgets(buf,80,fp_read))
    {
        //printf("\n");
        parameter_num=0;
        if(buf[0]=='\n'||buf[0]=='\0') continue;
        status = regexec(&reg, buf, nmatch, pmatch, 0);
        if(status == REG_NOMATCH)
            printf("NO MATCH\n");
        else if(status == 0){
            //printf("Match:\n");
            int i,j,k,yn=1;
            for(i=0;i<nmatch;i++) if(buf[pmatch[i].rm_so]!='\0') {
                if (yn)
                    for (j=0; j<INSTRUCTION_KIND&&i!=0; ++j)
                        if (i == op_kind[j]) {
                            kind_num = j + 1;
                            yn = 0;
                        }
                for (j=pmatch[i].rm_so,k=0; j<pmatch[i].rm_eo; ++j)
                    parameter[parameter_num][k++] = buf[j];
                parameter[parameter_num++][k]='\0';
                strcpy(parameter[parameter_num-1],StringUpper(parameter[parameter_num-1]));
            }
        }
        //int i;
        //for(i=0; i<parameter_num; ++i)
        //   printf("%s\n",parameter[i]);
        printf("%s",parameter[0]);
        MEM_W(program_pr) = Instruction2Binary(parameter,parameter_num,kind_num);
        //printf("::%d\n",MEM_W(program_pr));
        program_pr += 4;
        instruction_num += 1;
        //fprintf(fp_write,"%u\n",Instruction2Binary(parameter,parameter_num,kind_num));
    }
    MEM_W(CODE_BEGIN) = instruction_num;
    fclose(fp_read);
    //fclose(fp_write);
    regfree(&reg);
}

unsigned int Instruction2Binary(char (*parameter)[50], const int parameter_num, const int kind_num) //notice char (*)[50]
{
    char* func_string = parameter[1];
    unsigned int op=0, rs=0, rt=0, rd=0, sa=0, func=0, imm=0, address=0;
    unsigned int binary32 = 0;
    switch (kind_num) {
        case OP_NAME:                                                                      //J 1000
            address = String2Int(parameter[2]);
            if (strcmp("J",func_string)==0){
                op=2;
            }
            else if (strcmp("JAL",func_string)==0){
                op=3;
            }
            else
                printf("compile OP_NAME error!\n");
            binary32 = (op & 0x3f)<<26 | (address & 0x03ffffff);
            break;
        case OP_REG:                                                                      //op $to
            rd=RegName2ID(parameter[2]);
            if (strcmp("HFHI",func_string)==0){
                func=16;
            }
            else if (strcmp("HFLO",func_string)==0){
                func=18;
            }
            else
                printf("compile OP_REG error!\n");
            binary32 = (op & 0x3f)<<26 | (rs & 0x1f) << 21 | (rt & 0x1f) << 16 | \
                       (rd & 0x1f) << 11 | (sa & 0x1f) << 6 | (func & 0x3f);
            break;
        case OP_REG_REG:                                                                  //op $t0,$t1
            rs=RegName2ID(parameter[2]);
            rt=RegName2ID(parameter[3]);
            if (strcmp("MULT",func_string)==0){
                func=24;
            }
            else if (strcmp("MULTU",func_string)==0){
                func=25;
            }
            else if (strcmp("DIV",func_string)==0){
                func=26;
            }
            else if (strcmp("DIVU",func_string)==0){
                func=27;
            }
            else
                printf("compile OP_REG_REG error!\n");
            binary32 = (op & 0x3f)<<26 | (rs & 0x1f) << 21 | (rt & 0x1f) << 16 | \
                       (rd & 0x1f) << 11 | (sa & 0x1f) << 6 | (func & 0x3f);
            break;
        case OP_REG_IMM:                                                                   //op $t0,#100
            address=String2Int(parameter[3]);
            if (strcmp("LUI",func_string)==0){
                op=15;
                rt=RegName2ID(parameter[2]);
            }
            else if (strcmp("BLTZ",func_string)==0){
                op=1;
                rs=RegName2ID(parameter[2]);
            }
            else if (strcmp("BLEZ",func_string)==0){
                op=6;
                rs=RegName2ID(parameter[2]);
            }
            else if (strcmp("BGTZ",func_string)==0){
                op=7;
                rs=RegName2ID(parameter[2]);
            }
            else if (strcmp("BGEZ",func_string)==0){
                op=1;
                rt=1;
                rs=RegName2ID(parameter[2]);
            }
            else
                printf("compile OP_REG_IMM error!\n");
            binary32 = (op & 0x3f)<<26 | (rs & 0x1f) << 21 | (rt & 0x1f) << 16 | (address & 0xffff);
            break;
        case OP_REG_REG_REG:                                                            //op $t0,$t1,$t2
            rd = RegName2ID(parameter[2]);
            rs = RegName2ID(parameter[3]);
            rt = RegName2ID(parameter[4]);
            if (strcmp("MOVN",func_string)==0){
                func=11;
            }
            else if (strcmp("MOVZ",func_string)==0){
                func=10;
            }
            else if (strcmp("ADD",func_string)==0){
                func=32;
            }
            else if (strcmp("ADDU",func_string)==0){
                func=33;
            }
            else if (strcmp("SUB",func_string)==0){
                func=34;
            }
            else if (strcmp("SUBU",func_string)==0){
                func=35;
            }
            else if (strcmp("MUL",func_string)==0){
                op=28;
                func=2;
            }
            else if (strcmp("SLT",func_string)==0){
                func=42;
            }
            else if (strcmp("SLTU",func_string)==0){
                func=43;
            }
            else if (strcmp("AND",func_string)==0){
                func=36;
            }
            else if (strcmp("OR",func_string)==0){
                func=37;
            }
            else if (strcmp("XOR",func_string)==0){
                func=38;
            }
            else if (strcmp("NOR",func_string)==0){
                func=39;
            }
            else if (strcmp("SLLV",func_string)==0){
                swap(&rs,&rt);
                func=4;
            }
            else if (strcmp("SRAV",func_string)==0){
                swap(&rs,&rt);
                func=7;
            }
            else if (strcmp("SRLV",func_string)==0){
                swap(&rs,&rt);
                func=6;
            }
            else
                printf("compile OP_REG_REG_REG error!\n");
            binary32 = (op & 0x3f)<<26 | (rs & 0x1f) << 21 | (rt & 0x1f) << 16 | \
                       (rd & 0x1f) << 11 | (sa & 0x1f) << 6 | (func & 0x3f);
            break;
        case OP_REG_IMM_REG:                                                                  //SW $t0,100($t1)
            rs = RegName2ID(parameter[2]);
            address = String2Int(parameter[3]);
            rt = RegName2ID(parameter[4]);
            if (strcmp("LB",func_string)==0){
                op=32;
            }
            else if (strcmp("LH",func_string)==0){
                op=33;
            }
            else if (strcmp("LW",func_string)==0){
                op=35;
            }
            else if (strcmp("SB",func_string)==0){
                op=40;
            }
            else if (strcmp("SH",func_string)==0){
                op=41;
            }
            else if (strcmp("SW",func_string)==0){
                op=43;
            }
            else
                printf("compile OP_REG_IMM_REG error!\n");
            binary32 = (op & 0x3f)<<26 | (rs & 0x1f) << 21 | (rt & 0x1f) << 16 | (address & 0xffff);
            break;
        case OP_REG_REG_IMM:                                                             //op $t0,$t1,#1000
            rs = RegName2ID(parameter[2]);
            rt = RegName2ID(parameter[3]);
            address = String2Int(parameter[4]);
            if (strcmp("ADDI",func_string)==0){
                op=8;
            }
            else if (strcmp("ADDIU",func_string)==0){
                op=9;
            }
            else if (strcmp("SLTI",func_string)==0){
                op=10;
            }
            else if (strcmp("SLTIU",func_string)==0){
                op=11;
            }
            else if (strcmp("ANDI",func_string)==0){
                op=12;
            }
            else if (strcmp("ORI",func_string)==0){
                op=13;
            }
            else if (strcmp("XORI",func_string)==0){
                op=14;
            }
            else if (strcmp("BEQ",func_string)==0){
                op=4;
            }
            else if (strcmp("BNE",func_string)==0){
                op=5;
            }
            else
                printf("compile OP_REG_REG_IMM error!\n");
            binary32 = (op & 0x3f)<<26 | (rs & 0x1f) << 21 | (rt & 0x1f) << 16 | (address & 0xffff);
            break;
        default:
            printf("switch error\n");
            break;
    }
    return binary32;
}