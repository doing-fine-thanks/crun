
#include <stdio.h>
int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    printf("yo %s \n", argv[i]);
  }
}
