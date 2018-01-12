#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

   char buf[20];
   char prefix[] = "http://";
   strcpy(buf, prefix); // use strncopy
   char path[] = "utwente.nl";
   strncat(buf, path, sizeof(buf)); //sizeof(buf) should be sizeof(path)

}
