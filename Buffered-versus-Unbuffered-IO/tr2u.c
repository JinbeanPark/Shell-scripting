// Jinbean Park
// 805330751

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {

  char buf[1];
  int i, j;
  ssize_t chkEOF;

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
    chkEOF = read(0, buf, 1); // For the file descriptor, 0 = stdin, 1 = stdout, 2 = stderr
    if (chkEOF == -1) {
      fprintf(stderr, "%s\n", errno); // Return -1 and set errno to indicate the error.
      exit(1);
    }

    if (chkEOF == 0 || chkEOF == -1)
      break;

    for (i = 0; i < strlen(fromStr); i++) {
      if (buf[0] == fromStr[i]) {
	buf[0] = toStr[i];
	break;
      }
    }
    
    chkEOF = write(1, buf, 1);
    if (chkEOF == -1) {
      fprintf(stderr, "%s\n", errno);
      exit(1);
    }
  }

  return 0;
}
