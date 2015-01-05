#include <stdio.h>
#include "opcode.h"
#include "common.h"
#include "util.h"

void printOpcode(u1 *code)
{
    u4 len = convertInt(code);
    int i=0;
    int j;
    int p;
    int index = 0;
    code = code + 4;
    
    while(i<len) {
        printf("  [%4d] %s ", index++, ocode[code[i]]);
        p = operand[code[i++]]; 
        for(j=0; j<p; j++) {
            printf("%d, ", code[i++]);
        } 
        printf("\n");
    }
}
