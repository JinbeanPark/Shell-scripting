#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int cmp(const void* a, const void* b) { return ( frobcmp(*(char const**)a, *(char const **)b));}

int frobcmp(char const* a, char const* b);

int chkAllocateMemory(void* ptr); // Check whether the memory was allocated well or not.

void freeBufReg(char **encodedStr, char *fileContents, int numStr);

void freeBuffer(char** str, int lenRow); // Release the Dynamic memory.

int chkIOerror(); // Check whether the I/O error occurred or not.

void printStr(char** c, int lenRow); // Write out encoded lines in the sorted order.

int chkOptF = 0;

int main(int argc, char** argv) {

  int i, j = 0, numStr = 0;
  int row = 0, col = 0;
  char *fileContents;
  char **encodedStr;
  
  // Check the number of argument.
  if (argc == 1)  // Case 1. There is no argument. In other words, there is no the option '-f'
    chkOptF = 0;

  else if (argc == 2) { // Case 2. There is one argument. In other words, there is the option '-f'
    if (strcmp(argv[1], "-f") != 0) {
      fprintf(stderr, "Invalid option %c\n", argv[1]);
      exit(1);
    }
    else
      chkOptF = 1;
  }

  else {
    fprintf(stderr, "The number of argument is wrong\n");
    exit(1);
  }

  struct stat buf;
  if (fstat(0, &buf) != 0) {
    fprintf(stderr, "Failed to obtain information about an open file\n");
    exit(1);
  }
  
  // Check whether the input is regualr file or not.
  // Case 1. When the input is regular file.
  if (S_ISREG(buf.st_mode)) { 
    
    if (buf.st_size == 0) return 0; // Check whether the file is empty or not.
    
    fileContents = (char*)malloc(sizeof(char) * buf.st_size);
    if (!chkAllocateMemory(fileContents)) exit(1);
    
    if (read(0, fileContents, buf.st_size) == -1) {
      fprintf(stderr, "Failed to read the file\n");
      free(fileContents);
      exit(1);
    }

    // Check how many strings are there in file through checking the number of white space.
    for (i = 0; i < buf.st_size; i++)
      if (fileContents[i] == ' ') numStr++;
    numStr++; // Because the number of strings == (the number of white space) + 1
    
    encodedStr = (char**)malloc(sizeof(char*) * numStr);
    if (!chkAllocateMemory(encodedStr)) {
      free(fileContents);
      exit(1);
    }
    
    fileContents[buf.st_size - 1] = ' ';
 
    for (i = 0; i < numStr; i++) {
      encodedStr[i] = &fileContents[j];
      while (fileContents[j] != ' ') j++;
      j++;
    }
  }
  
  // Case 2. When the input is not regular file (+growing file)
  
  else {
    char bufByte[1];
    ssize_t chkEOF;
    
    chkEOF = read(0, bufByte, 1); // Check failed to read and reached to EOF
    if (chkEOF == -1) {
      fprintf(stderr, "Failed to read\n");
      exit(1);
    }
    if (chkEOF == 0) return 0; // Empty
    
    encodedStr = (char**)malloc(sizeof(char*) * (row + 1));
    if (!chkAllocateMemory(encodedStr))
      exit(1);

    encodedStr[row] = (char*)malloc(sizeof(char) * (col + 1));
    if (!chkAllocateMemory(encodedStr[row])) {
      free(encodedStr);
      exit(1);
    }

    while (chkEOF > 0) {
      if (bufByte[0] == ' ') {
	encodedStr[row++][col] = bufByte[0];
	col = 0;
	char **tempBuffer = encodedStr;
	encodedStr = (char**)realloc(encodedStr, sizeof(char*) * (row + 1));
	if (!chkAllocateMemory(encodedStr)) {
	  freeBuffer(tempBuffer, row);
	  exit(1);
	}
	
	encodedStr[row] = (char*)malloc(sizeof(char));
	if (!chkAllocateMemory(encodedStr[row])) {
	  freeBuffer(encodedStr, row + 1);
	  exit(1);
	}
      }
      else {
	encodedStr[row][col++] = bufByte[0];
	char* tempBuffer = encodedStr[row];
	encodedStr[row] = (char*)realloc(encodedStr[row], sizeof(char) * (col + 1));
	if (!chkAllocateMemory(encodedStr[row])) {
	  free(tempBuffer);
	  freeBuffer(encodedStr, row + 1);
	  exit(1);
	}
      }
      chkEOF = read(0, bufByte, 1);
      if (chkEOF == -1) {
	fprintf(stderr, "Failed to read\n");
	exit(1);
      }
    }
    encodedStr[row][col] = ' ';
  }
  
  // Sort the strings
  (S_ISREG(buf.st_mode)) ? qsort(encodedStr, numStr, sizeof(char*), cmp) : qsort(encodedStr, row + 1, sizeof(char*), cmp);

  // Print the strings
  (S_ISREG(buf.st_mode)) ? printStr(encodedStr, numStr) : printStr(encodedStr, row + 1);
  
  // Free the buffers
  (S_ISREG(buf.st_mode)) ? freeBufReg(encodedStr, fileContents, numStr) : freeBuffer(encodedStr, row + 1);

  return 0;
}


int frobcmp(char const* a, char const* b) {

  if (a == NULL || b == NULL) {
    fprintf(stderr, "At least  one character array is empty\n");
    exit(1);
  }

  int index = 0;
  if (chkOptF == 0) {
    while (a[index] != ' ' && b[index] != ' ') {
      if (a[index] == b[index]) index++;
      else return ((a[index] ^ 42) > (b[index] ^ 42)) ? 1: -1;
    }
  }
  else if (chkOptF == 1) {
    while (a[index] != ' ' && b[index] != ' ') {
      if (a[index] == b[index]) index++;
      else return (toupper((unsigned char)(a[index] ^ 42)) > toupper((unsigned char)(b[index]) ^ 42)) ? 1 : -1;
    }
  }

  if (a[index] == ' ' && b[index] == ' ') return 0;
  else if (a[index] != ' ' && b[index] == ' ') return 1;
  else return -1;
}

int chkAllocateMemory(void* ptr) {

  if (ptr == NULL) {
    fprintf(stderr, "Memory was not allocated\n");
    return 0;
  }
  return 1;
}

void freeBufReg(char **encodedStr, char *fileContents,int numStr) {

  if (encodedStr != NULL)
    free(encodedStr);
  
  if (fileContents != NULL)
    free(fileContents);
}

void freeBuffer(char** str, int lenRow) {

  int i;
  for (i = 0; i < lenRow; i++)
    free(str[i]);
  free(str);
}

int chkIOerror() {
  if (ferror(stdout) || ferror(stdin)) {
    fprintf(stderr, "I/O error happened\n");
    return 0;
  }
  return 1;
}

void printStr(char** c, int lenRow) {

  int ro, co = 0;
  for (ro = 0; ro < lenRow; ro++) {
    while (c[ro][co] != ' ') {
      ssize_t chkErr = write(1, &c[ro][co++], 1);
      if (chkErr == -1) {
	fprintf(stderr, "Happened I/O error\n");
        exit(1);
      }
    }
    ssize_t chkErr = write(1, " ", 1);
    if (chkErr == -1) {
      fprintf(stderr, "Happened I/O error\n");
      exit(1);
    }
    co = 0;
  }
}
