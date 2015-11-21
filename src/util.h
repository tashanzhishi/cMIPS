//
// Created by wyb on 15-11-19.
//

#ifndef CMIPS_UTIL_H
#define CMIPS_UTIL_H

#define CODE_BEGIN 0
#define DATA_BEGIN 512

#define MEM_B(addr) (MEM[addr])
#define MEM_H(addr) (*(short*)(MEM+addr))
#define MEM_W(addr) (*(int*)(MEM+addr))

extern char* StringUpper(const char* src);
extern unsigned int RegName2ID(const char* name);
extern int String2Int(const char* stc);
extern void swap (unsigned int* num1, unsigned int* num2);

#endif //CMIPS_UTIL_H
