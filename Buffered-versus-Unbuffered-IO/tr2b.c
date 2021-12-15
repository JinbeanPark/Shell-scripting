// Jinbean Park
// 805330751

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
  
  char ch;
  int i, j;

  // Check the number of arguments.
  if (argc < 3) {
    fprintf(stderr, "The number of argument is less than 2\n");
    exit(1);
  }
  else if (argc > 3) {
    fprintf(stderr, "The number of argument is more than 2\n");
    exit(1);
  }

  char *fromStr = argv[1];
  char *toStr = argv[2];

  // Check whether the length of two operlands are same or not.
  if (strlen(fromStr) != strlen(toStr)) {
    fprintf(stderr, "The length of Two operlands are different\n");
    exit(1);
  }

  // Check the case of duplicate byte.
  for (i = 0; i < strlen(fromStr) - 1; i++) {
    for (j = i + 1; j < strlen(fromStr); j++) {
      if (fromStr[i] == fromStr[j]) {
	fprintf(stderr, "From operland has the duplicate byte\n");
	exit(1);
      }
    }
  }

  while (1) {
    ch = getchar();
    if (ferror(stdin)) {
      fprintf(stderr, "Happened I/O error\n");
      exit(1);
    }
       
    if (feof(stdin))
      break;

    for (i = 0; i < strlen(fromStr); i++) {
      if (ch == fromStr[i]) {
	ch = toStr[i];
	break;
      }
    }
    putchar(ch);
    if (ferror(stdout)) {
      fprintf(stderr, "Happened I/O error\n");
      exit(1);
    }
  }

  return 0;
}
