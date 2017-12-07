#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char src[9], dest[9];
    char* base_url = "www.ru.nl";

    strncpy(src, base_url, 9);
    strcpy(dest, src);
}   
