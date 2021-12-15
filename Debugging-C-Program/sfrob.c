#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) { return ( frobcmp(*(char const**)a, *(char const **)b));}

int frobcmp(char const* a, char const* b);

int chkAllocateMemory(void* ptr); // Check whether the memory was allocated well or not.

void freeBuffer(char** str, int lenRow); // Release the Dynamic memory.

int chkIOerror(); // Check whether the I/O error occurred or not.

void printStr(char** c, int lenRow); // Write out encoded lines in the sorted order.


int main() {
  
  int row, col;
  row = col = 0;
  
  char** encodedStr;
  
  encodedStr = (char**)malloc(sizeof(char*));
  if (!chkAllocateMemory(encodedStr)) exit(1);
  
  encodedStr[row] = (char*)malloc(sizeof(char));
  if (!chkAllocateMemory(encodedStr[row])) {
    free(encodedStr);
    exit(1);
  }

  char ch = getchar();
  if (!chkIOerror()) {
    freeBuffer(encodedStr, row + 1);
    exit(1);
  }

  while (!feof(stdin)) {
    
    if (ch == ' ') {
      encodedStr[row++][col] = ch;
      col = 0;
      char** tempBuffer = encodedStr;
      encodedStr = (char**)realloc(encodedStr, sizeof(char*) * (row + 1));
      if (!chkAllocateMemory(encodedStr)) {
	freeBuffer(tempBuffer, row + 1);
	exit(1);
      }

      encodedStr[row] = (char*)malloc(sizeof(char));
      if (!chkAllocateMemory(encodedStr[row])) {
	freeBuffer(tempBuffer, row + 1);
	exit(1);
      }
    }
    else {
      encodedStr[row][col++] = ch;
      char* tempBuffer = encodedStr[row];
      encodedStr[row] = (char*)realloc(encodedStr[row], sizeof(char) * (col + 1));
      if (!chkAllocateMemory(encodedStr[row])) {
	free(tempBuffer);
	freeBuffer(tempBuffer, row + 1);
	exit(1);
      }
    }

    ch = getchar();
    if (!chkIOerror()) {
    freeBuffer(encodedStr, row + 1);
    exit(1);
    }
  }

  encodedStr[row][col] = ' ';
  
  qsort(encodedStr, row + 1, sizeof(char*), cmp);
  
  printStr(encodedStr, row + 1);

  freeBuffer(encodedStr, row + 1);

  return 0;
}


int frobcmp(char const* a, char const* b) {
  
  if (a == NULL || b == NULL) {
    fprintf(stderr, "At least  one character array is empty\n");
    exit(1);
  }

  int index = 0;
  while (a[index] != ' ' && b[index] != ' ') {
    if (a[index] == b[index]) index++;
    else return ((a[index] ^ 42) > (b[index] ^ 42)) ? 1: -1;
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
    while (c[ro][co] != ' ') printf("%c", c[ro][co++]);
    printf(" ");
    co = 0;
  }
}
