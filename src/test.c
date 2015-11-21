//
// Created by wyb on 15-11-15.
//

#include<stdio.h>
#include<string.h>
#include <regex.h>
#include "instruction.h"
#include "util.h"
#include "compiler.h"
#include "register.h"
#include "decode.h"


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
    SB (1,0,1); //MEM[1]=REG[1]低8位
    SH (2,0,10); //MEM[2]=REG[2]低16位
    SW (3,0,20); //MEM[3]=REG[3]低32位
    printf ("0x%08x 0x%08x 0x%08x\n",MEM_B(1),MEM_H(10),MEM_W(20));

    REG[R_S0]=300, REG[R_S1]=200;
    ADD (R_S2,R_S0,R_S1);
    printf ("%d\n",REG[R_S2]);
}

void TestRegex()
{
    const char* op_loop = "(\\w+)\\s+(\\w+)\\s*";
    const char* op_reg = "(\\w+)\\s+(\\$\\w+)\\s*";
    const char* op_reg_reg = "(\\w+)\\s+(\\$\\w+)\\s*,\\s*(\\$\\w+)\\s*";
    const char* op_reg_imm = "(\\w+)\\s+(\\$\\w+)\\s*,\\s*(#[0-9]+)\\s*";
    const char* op_reg_reg_reg = "(\\w+)\\s+(\\$\\w+)\\s*,\\s*(\\$\\w+)\\s*,\\s*(\\$\\w+)\\s*";
    const char* op_reg_imm_reg = "(\\w+)\\s+(\\$\\w+)\\s*,\\s*([0-9]+)\\((\\$\\w+)\\)";
    const char* op_reg_reg_imm = "(\\w+)\\s+(\\$\\w+)\\s*,\\s*(\\$\\w+)\\s*,\\s*\\#([0-9]+)";
    char pattern[1000];
    sprintf(pattern,"%s|%s|%s|%s|%s|%s|%s",op_loop,op_reg,op_reg_reg,op_reg_imm,op_reg_reg_reg,op_reg_imm_reg,op_reg_reg_imm);
    //sprintf(pattern,"%s|%s",op_loop,op_reg);
    //printf("%s\n",pattern);
    //const int group_index[7][2] = {{1,2},{3,4},{5,7},{8,10},{11,14},{15,18},{19,22}};
    //const int group_num = 7;
    regex_t reg;
    regcomp(&reg, pattern, REG_EXTENDED|REG_NEWLINE);
    int status;
    regmatch_t pmatch[23];
    const int nmatch = 23;

    char buf[80];
    FILE* fp = fopen("program.mips","rb");
    if(fp==NULL)
        printf("fopen error\n");
    char parameter[20];
    while(fgets(buf,80,fp))
    {
        if(buf[0]=='\n'||buf[0]=='\0') continue;
        status = regexec(&reg, buf, nmatch, pmatch, 0);
        if(status == REG_NOMATCH)
            printf("NO MATCH\n");
        else if(status == 0){
            printf("Match:\n");
            int i,j,k;
            for(i=0;i<nmatch;i++) if(buf[pmatch[i].rm_so]!='\0') {
                printf("group%d: ",i);
                for (j=pmatch[i].rm_so,k=0; j<pmatch[i].rm_eo; ++j)
                    parameter[k++] = buf[j];
                parameter[k]='\0';
                printf("%s\n",parameter);
                    //printf("%c", buf[j]);
                //printf("\n");
            }
            printf("\n");
        }
    }
    fclose(fp);
    regfree(&reg);
}

void TestDecode()
{
    memset (REG,sizeof(REG),0);
    DecodeAndExecute();
    printf("\n****result****\n");
    int i=0;
    for (i=DATA_BEGIN; i<DATA_BEGIN+80; i+=4)
        printf("%d: %d\n",i,MEM_W(i));
}

int main ()
{
    //TestMemory();
    //TestRegex();
    CompileMIPS();
    //DecodeAndExecute();
    TestDecode();
    return 0;
}