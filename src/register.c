//
// Created by wyb on 15-11-16.
//

#include "register.h"

const int INT_MAX = 0x79999999;
const int INT_MIN = 0x80000000;

int REG[REG_SIZE]={0};
unsigned char MEM[MEM_SIZE]={0};

const char* kRegisterSet[REG_SIZE] = {
        "ZERO", "AT", "V0", "V1", "A0", "A1", "A2", "A3",
        "T0", "T1", "T2", "T3", "T4", "T5", "T6", "T7", "S0", "S1", "S2", "S3",
        "S4", "S5", "S6", "S7", "T8", "T9", "K0", "K1", "GP", "SP", "FP", "RA",
        "PC", "HI", "LO"
};