#include "func.h"
#include <string.h>
int main(int argc, char ** argv)
{
    overfprintf(stdout, "   %Ro %Cv %to %d %p", 2210, 255, 16, "00000000000000000000000000000000001", 36, 32, NULL);
    overfprintf(stdout, "   3999 = %Ro\n\n", 3999);
    overfprintf(stdout, "   1 = %Zr\n\n", 1);
    overfprintf(stdout, "   123 base 8 = %Cv\n\n", 123, 8);
    overfprintf(stdout, "   170 base 16 = %CV\n\n", 170, 16);
    overfprintf(stdout, "   '1010' base 2 = %to\n\n", "1010", 2);
    overfprintf(stdout, "   'ABC' base 16 = %TO\n\n", "ABC", 16);
    overfprintf(stdout, "   -1 = %mi\n\n", -1);
    overfprintf(stdout, "   65535 = %mu\n\n", 65535u);
    overfprintf(stdout, "   3.14 = %md\n", 3.14);
    overfprintf(stdout, "   2.5 = %mf\n\n", 2.5f);
    char result[256];
    oversprintf(result, "Roman=%Ro, Hex=%Cv, Memory=%mi", 123, 123, 16, 123);
    printf("   %s\n", result);
    
    return 0;
}