Jinbean Park
805330751

Laboratory: Debugging a C program

1. Download the coreutils-with-bug and unzip the coreutils-with-bug.tar.gz

Command:

wget web.cs.ucla.edu/classes/winter20/cs35L/assign/coreutils-with-bug.tar.gz

tar -xzvf coreutils-with-bug.tar.gz

2. Make the directoy to install the coreutils-with-bug in the directoy.

Command:

mkdir coreutilsWithBug

cd coreutilsWithBug

pwd <= To check the absolute path

Output:

/u/cs/ugrad/jinbean/coreutilsWithBug

3. Build coreutils as-is

Command:

cd coreutils-with-bug

./configure --prefix=/u/cs/ugrad/jinbean/coreutilsWithBug

make

Output:

In file included from utimecmp.c:41:0:
utimens.h:2:5: error: conflicting types for 'futimens'
 int futimens (int, char const *, struct timespec const [2]);
     ^
In file included from utimecmp.h:25:0,
                 from utimecmp.c:25:
/usr/include/sys/stat.h:373:12: note: previous declaration of 'futimens' was here
 extern int futimens (int __fd, const struct timespec __times[2]) __THROW;
            ^
make[3]: *** [utimecmp.o] Error 1
make[3]: Leaving directory `/w/home.25/cs/ugrad/jinbean/coreutils-with-bug/lib'
make[2]: *** [all] Error 2
make[2]: Leaving directory `/w/home.25/cs/ugrad/jinbean/coreutils-with-bug/lib'
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory `/w/home.25/cs/ugrad/jinbean/coreutils-with-bug'
make: *** [all] Error 2


4. What problems did you have when building it as-is?

I got some build error. The reason why the build error occurred
because there is another function having the same name with the function 'futimens'.

5. Download the coreutils.diff in the directory "coreutils-with-bug"

Command:
wget web.cs.ucla.edu/classes/winter20/cs35L/assign/coreutils.diff

6. Patch to replace the "futimens" into "coreutils_futimens".

Command:
patch -p0 < coreutils.diff

Output:
patching file lib/utimens.c
patching file lib/utimens.h
patching file src/copy.c
patching file src/tee.c
patching file src/touch.c

7. Re-build and install.

Command:
make
make install

Note:
I did not get any errors after rebuilding and installing the coreutils.
In other words, it means that the errors were fixed successfully after patching!

8. Why did the renaming patch fix them?

The reason is that the original function "futimens" was conflicted with the another function
having same with "futimens", but we replaced the name  of function "futimens" with "coreutils_futimens".
In addition, the instance of "static bool tee" was changed to "static bool coreutils-tee" by patching.
As a result, the conflicting errors were resolved by renaming the functions.

9. Reproduce the problem.

Command:
tmp=$(mktemp -d)
cd $tmp
touch -d '1918-11-11 11:00 GMT' wwi-armistice-cs35L
touch now
sleep 1
touch now1
TZ=UTCO ls -lt --full-time wwi-armistice-cs35L now now1

Output:
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 05:19:03.251470140 +0000 now1
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 05:18:52.722287047 +0000 now
-rw-r--r-- 1 jinbean csugrad 0 1918-11-11 11:00:00.000000000 +0000 wwi-armistice-cs35L

Note:
Output looks normal, but we have to use the ls in the directory "/u/cs/ugrad/jinbean/coreutilsWithBug/bin" to reproduce the buggy.

Command:
TZ=UTCO /u/cs/ugrad/jinbean/coreutilsWithBug/bin/ls -lt --full-time wwi-armistice now now1

Output:
-rw-r--r-- 1 jinbean csugrad 0 1918-11-11 11:00:00.000000000 +0000 wwi-armistice
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 06:26:22.056786374 +0000 now1
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 06:26:15.680675213 +0000 now

Note:
The order of now1 and now is still same as the order using non-buggy version, but wwi-armistice moved to top after 
using the command ls with buggy version. In other words, the problem is reproduced.

10. Use a debugger to figure out what went wrong

Command:

cd coreutils-with-bug

cd src

emacs ls.c <= To find the functions related to the time or sort.

C-s t i m e

C-s <= typed over and over agian until found the functions "compare_ctime", "compare_mtime", "compare_atime"

C-x C-c <= Exit emacs because I found the functions related to the time or sort.

gdb ls <= Run the command 'ls' while debugging through using GDB.

break compare_ctime <= Set the break point to the function "compare_ctime".

run -lt

Note:
Exit normally. In other words, program didn't go through the function "compare_ctime" while running the command ls -lt,
so there is no problem in the function "compare_ctime".

Command:

break compare_mtime

run -lt

Note: Program was stopped at the function "compare_mtime"

Output:
2884	static int compare_mtime (V a, V b) { return cmp_mtime (a, b, xstrcoll); }

Command:

list <= Print the ten lines.

step <= execute the one line code, and the program get into the function if there is a function on the line.
        Got into the function cmp_mtime(a, b, xstrcoll).

list

step <= Got into the function "timespec_cmp (struct a, struct timespec b)"

list

Note:
I found the problem inside the function "timespec_cmp (struct a, struct timespec b)"
The problem is that it is possible to occurr the overflow on variable "diff",
so I edited the code inside the function "timespec_cmp (struct a, struct timespec b)"

11. Fix the corresponding source file.

Before changing:
int diff = a.tv_sec - b.tv_sec;
return diff ? diff : a.tv_nsec - b.tv_nsec;

after changing:
if (a.tv_sec == b.tv_sec) return a.tv_nsec - b.tv_nsec;
return (a.tv_sec > b.tv_sec) ? 1 : -1;


12. Construct a new patch file lab4.diff containing your coreutils fixes, in the form of a ChangeLog entry followed
    by a diff -u patch.

Command:

cd ../

mkdir bugTimespec <= To copy the buggy version of timespec.h

cp lib/timespec.h bugTimespec/timespec.h

cd lib

emacs timespec.h <= To change the code

Note:
Before changing:
int diff = a.tv_sec - b.tv_sec;
return diff ? diff : a.tv_nsec - b.tv_nsec;

After changing:
if (a.tv_sec == b.tv_sec) return a.tv_nsec - b.tv_nsec;
return (a.tv_sec > b.tv_sec) ? 1 : -1;

Command:

C-x C-c

cd ../

make

cd src

pwd

Output:
/u/cs/ugrad/jinbean/coreutils-with-bug/src <= Get the absolute path to check whether bug is fixed or not.

tmp=$(mktemp -d)
cd $tmp
touch -d '1918-11-11 11:00 GMT' wwi-armistice-cs35L
touch now
sleep 1
touch now1
/u/cs/ugrad/jinbean/coreutils-with-bug/src/ls -lt

Output:
otal 0
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 03:36 now1
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 03:36 now
-rw-r--r-- 1 jinbean csugrad 0 1918-11-11 03:00 wwi-armistice

Note:
we are able to check that bug is fixed from the above output.

Command:
cd /u/cs/ugrad/jinbean/coreutils-with-bug/
diff -u lib/timespec.h bugTimespec/timespec.h > timespec.diff

Note:
I made the patch file "timespec.diff"

Command:
emacs

C-x 4 a <= To put the contents of patch

The contents of Changelog:

timespec.h
Edited the code because of occurring the overflow,
so the command ls -lt come to be able to sort the files correctly.

Command:
cat ChangeLog >> lab4.diff
cat timespec.diff >> lab4.diff

13. Try to reproduce the problem in your home directory on the SEASnet Linux servers, instead of using the $tmp directory.
    How well does SEASnet do?

Command:

cd ~/
touch -d '1918-11-11 11:00 GMT' wwi-armistice-cs35L
touch now
sleep 1
touch now1
TZ=UTCO ls -lt --full-time wwi-armistice-cs35L now now1

Output:
-rw-r--r-- 1 jinbean csugrad 0 2054-12-17 17:28:16.000000000 +0000 wwi-armistice-cs35L
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 12:06:53.246728000 +0000 now1
-rw-r--r-- 1 jinbean csugrad 0 2020-02-06 12:06:46.477688000 +0000 now

Note:
The files are sorted correctlys but the date of wwi-armistice-cs35L looks wrong
because the date of wwi-armistice-cs35L is changed to 2054-12-17 which is indicate
the future. I think the reason why the date is displayed to 2054-12-17 is that
the date of wwi-armistice-cs35L is so big negative number,
so underflows occurred. Therefore, big negative number was converted
to big positive number because of underflow.
