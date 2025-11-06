#include "func.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    
    printf("=== Testing overfprintf ===\n\n");
    
    printf("1. %%Ro - Roman numerals:\n");
    overfprintf(stdout, "   1984 = %Ro\n", 1984);
    overfprintf(stdout, "   49 = %Ro\n", 49);
    overfprintf(stdout, "   3999 = %Ro\n\n", 3999);
    
    printf("2. %%Zr - Zeckendorf representation:\n");
    overfprintf(stdout, "   10 = %Zr\n", 10);
    overfprintf(stdout, "   20 = %Zr\n", 20);
    overfprintf(stdout, "   1 = %Zr\n\n", 1);
    
    printf("3. %%Cv - Base conversion (lowercase):\n");
    overfprintf(stdout, "   255 base 16 = %Cv\n", 255, 16);
    overfprintf(stdout, "   42 base 2 = %Cv\n", 42, 2);
    overfprintf(stdout, "   123 base 8 = %Cv\n\n", 123, 8);
    
    printf("4. %%CV - Base conversion (uppercase):\n");
    overfprintf(stdout, "   255 base 16 = %CV\n", 255, 16);
    overfprintf(stdout, "   170 base 16 = %CV\n\n", 170, 16);
    
    printf("5. %%to - String to int (lowercase):\n");
    overfprintf(stdout, "   'ff' base 16 = %to\n", "ff", 16);
    overfprintf(stdout, "   '1010' base 2 = %to\n\n", "1010", 2);
    
    printf("6. %%TO - String to int (uppercase):\n");
    overfprintf(stdout, "   'FF' base 16 = %TO\n", "FF", 16);
    overfprintf(stdout, "   'ABC' base 16 = %TO\n\n", "ABC", 16);
    
    printf("7. %%mi - Memory dump int:\n");
    overfprintf(stdout, "   255 = %mi\n", 255);
    overfprintf(stdout, "   -1 = %mi\n\n", -1);
    
    printf("8. %%mu - Memory dump unsigned int:\n");
    overfprintf(stdout, "   255 = %mu\n", 255u);
    overfprintf(stdout, "   65535 = %mu\n\n", 65535u);
    
    printf("9. %%md - Memory dump double:\n");
    overfprintf(stdout, "   3.14 = %md\n", 3.14);
    
    printf("10. %%mf - Memory dump float:\n");
    overfprintf(stdout, "   2.5 = %mf\n\n", 2.5f);
    
    printf("11. Testing oversprintf:\n");
    char result[256];
    oversprintf(result, "Combined: Roman=%Ro, Hex=%Cv, Memory=%mi", 123, 123, 16, 123);
    printf("   %s\n", result);
    
    return 0;
}