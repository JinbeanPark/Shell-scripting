Jinbean Park
805330751

Laboratory: Buffered versus unbuffered I/O

1. Write a C transliteration program tr2b.c that uses getchar and putchar to transliterate bytes as described above.

Note:

#include <stdio.h>
=> To use fprintf(), getchar(), putchar(), ferror(), feof(), and so on.

#include <stdlib.h>
=> To use exit().

#include <string.h>
=> To use strlen().

argc
=> The number of arguments.

argv
=> The strings of each argument.

The flow of tr2b.c
1) Check the number of arguments
2) Check whether the length of two operlands are same or not
3) Check the case of duplicate byte.
4) Transliterate if the program find out the character in From(=First operland) from the input.


2. Write a C program tr2u.c that uses read and write to transliterate bytes, instead of using
   getchar and putchar.

#include <unistd.h>
=> To use read() and write()

#include <errno>
=> To use errono to indicate the error.

read(0, buf, 1)
=> 0 means stdin
=> buf means the location for saving
=> 1 means the number of bytes to read

write(1, buf, 1)
=> 1 means stdout
=> buf means buffer to write to
=> the number of bytes to write

The flow of tr2u.c is same as tr2b.c


3. Use the strace command to compare the system calls issued by your tr2b and tr2u commands.

(a) when copying one file to another.

Command:

touch output.txt

head --bytes=5000000 /dev/urandom > output.txt

man strace

strace -c ./tr2b 'A' 'B' < output.txt > tr2b_output.txt

Output:
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 55.39    0.000699           1       611           write
 28.13    0.000355           1       613           read
  5.94    0.000075           8         9           mmap
  3.49    0.000044          11         4           mprotect
  1.90    0.000024           6         4           fstat
  1.51    0.000019          10         2           open
  1.27    0.000016          16         1           munmap
  0.71    0.000009           9         1         1 access
  0.63    0.000008           4         2           close
  0.40    0.000005           5         1           execve
  0.32    0.000004           4         1           brk
  0.32    0.000004           4         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.001262                  1250         1 total

Command:

strace -c ./tr2u 'A' 'B' < output.txt > tr2u_output.txt

Output:

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 54.97   23.442769           5   5000000           write
 45.03   19.202022           4   5000002           read
  0.00    0.000033           8         4           mprotect
  0.00    0.000031           4         7           mmap
  0.00    0.000012          12         1           munmap
  0.00    0.000009           5         2           open
  0.00    0.000004           2         2           close
  0.00    0.000004           2         2           fstat
  0.00    0.000004           4         1           arch_prctl
  0.00    0.000000           0         1           brk
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00   42.644888              10000024         1 total


Note: The reason why tr2u has much more system calls than tr2b
because the tr2b is buffered version, so the functions "getchar" and "putchar"
in tr2b do not require system calls a lot compared to the the tr2u
which is unbuffered version. In other words, the functions
"read" and "write" in tr2u require much more system calls than tr2b.
As a result, tr2u took much more time than tr2b.


(b) when copying a file to your terminal.

Command: strace -c ./tr2b 'A' 'B' < output.txt

Output:

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 97.83    0.066417           3     19897           write
  2.17    0.001476           2       613           read
  0.00    0.000000           0         2           open
  0.00    0.000000           0         2           close
  0.00    0.000000           0         4           fstat
  0.00    0.000000           0         9           mmap
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         1           brk
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.067893                 20536         1 total


Command: strace strace -c ./tr2u 'A' 'B' < output.txt

Output:

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 55.73   28.160645           6   5000000           write
 44.27   22.366870           4   5000002           read
  0.00    0.000076          11         7           mmap
  0.00    0.000043          11         4           mprotect
  0.00    0.000024          12         2           open
  0.00    0.000021          21         1           munmap
  0.00    0.000015           8         2           fstat
  0.00    0.000011          11         1           brk
  0.00    0.000009           5         2           close
  0.00    0.000008           8         1         1 access
  0.00    0.000008           8         1           execve
  0.00    0.000007           7         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00   50.527737              10000024         1 total

Note: tr2b and tr2u copying a file to the terminal tooks much more time 
than tr2b and tr2u copying one file to another because the tr2b and tr2u
have to output on the screen.


4. Use the time command to measure how much faster one program is, compare to 
   the other, when copying the same amount of data.

(a) when copying one file to another.

Command:

time ./tr2b 'A' 'B' < output.txt > tr2b_output.txt

Output:

real	0m0.320s
user	0m0.268s
sys	    0m0.007s

Command:

time ./tr2u 'A' 'B' < output.txt > tr2u_output.txt

Output:

real	0m12.977s
user	0m3.245s
sys	    0m9.689s

(b) when copying a file to your terminal.

Command:

time ./tr2b 'A' 'B' < output.txt

Output:

real	0m0.848s
user	0m0.312s
sys	    0m0.097s

Command:

time ./tr2u 'A' 'B' < output.txt

Output:

real	0m12.171s
user	0m3.339s
sys	    0m8.818s


Note: 
The buffered version took less time than the unbuffered version
because the unbuffered version require much more system calls than
the buffered version.
