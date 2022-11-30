#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
int main(int argc, char const *argv[])
{
    int quotient;
    for (int quotient = 1; quotient  <=(100 / 5); quotient = quotient + 1) {
    printf("%d\n", 5 * quotient);
    }
    
}


