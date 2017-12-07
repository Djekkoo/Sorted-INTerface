#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    f(1);

}

void f(int x) {
    char buf[8];
    gets(buf); //dangerous functions
}

void format_hard_disk() {
    printf("Format hard disk");
}