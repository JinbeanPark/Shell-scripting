Jinbean Park
805330751

Assignment 6. Dynamic linking

Laboratory: Who's linked to what?

1. Compile, build and run the program simpgmp.c in C on the SEASnet GNU/Linux servers.
   Since it uses GMP you will need to use the linker flag -lgmp to build this program.

Command:

wget http://web.cs.ucla.edu/classes/winter20/cs35L/assign/simpgmp.c

gcc -lgmp simpgmp.c -o simpgmp

Note:

I got the source code simpgmp.c and compiled simpgmp.c by using the linker flag -lgmp.



2. Use the program to compute 2**24 (i.e., 2^24, or 2 to the 24th power) and 2**(2**24);
   verify that the latter number has 5,050,446 decimal digits, starts with "1818" and ends
   with "7536".

Command:

./simpgmp 24

Output:
16777216

Command:

./simpgmp 16777216

Output: 

Printed out so many characters

Command:

./simpgmp 16777216 > resultSimpgmp.txt

man wc

Note:

I found the option -m on command "wc".

-m, --chars => print the character counts

Command:

cat resultSimpgmp.txt | wc -m

Output:

5050447

Note:

The output is 5050447, but the number of decimal digits are "5050446"

because the last character is not decimal digit.

Therefore, I was able to check out the number of decimal digits are 5050446 from the above output.

Command:

head -c 4 resultSimpgmp.txt

Output:

1818

Note:

I was able to check the first four decimal digits are "1818" from the above output.

Command:

tail -c 5 resultSimpgmp.txt

Output:

7536

Note:

I was able to check the last four decimal digits are "7536" from the above output.


3. Use the ldd command to see which dynamic libraries your simple program uses.

Command:

ldd ./simpgmp

Output:

linux-vdso.so.1 =>  (0x00007ffc783e8000)
libgmp.so.10 => /lib64/libgmp.so.10 (0x00007fe8e8e41000)
libc.so.6 => /lib64/libc.so.6 (0x00007fe8e8a73000)
/lib64/ld-linux-x86-64.so.2 (0x00007fe8e90b9000)


4. 

1) Use the strace command to see which system calls your simple program makes.

Command:

strace -c ./simpgmp 24

Output:

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 26.25    0.000042           4        10           mmap
 23.75    0.000038           6         6           mprotect
 12.50    0.000020           7         3           open
  6.25    0.000010          10         1           munmap
  5.62    0.000009           2         4           brk
  5.00    0.000008           8         1           write
  4.38    0.000007           2         4           fstat
  4.38    0.000007           7         1           execve
  3.75    0.000006           3         2           read
  3.75    0.000006           6         1         1 access
  3.12    0.000005           2         3           close
  1.25    0.000002           2         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000160                    37         1 total

2) Which of these calls are related to dynamic linking and what is the relationship?

(1) open(): dlopen() is implemented by opening the target library with the system call open()

(2) mmap(): Mapping it into memory with mmap()


5. Suppose your student ID is the 9-digit number nnnnnnnnn. On a SEASnet GNU/Linux server,
   run the shell command "ls /usr/bin | awk '(NR-nnnnnnnnn) % 251 == 0'" to get a
   list of nine or so commands to investigate.

Command:

ls /usr/bin | awk '(NR-805330751)%251 == 0'

Output:

abrt-action-analyze-vulnerability
cifsiostat
dwp
gnomevfs-df
infokey
ldns-dane
neato
pamtohdiff
pmdate
pstree
sgmldiff
ttmkfdir
ypdomainname


6. Invoke ldd on each command in your list.
   If there are error messages, investigate why they're occurring

Command + Output:

[jinbean@lnxsrv09 ~]$ ldd /usr/bin/abrt-action-analyze-vulnerability
	not a dynamic executable
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/cifsiostat
	linux-vdso.so.1 =>  (0x00007ffe2b327000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f4d6282f000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f4d62bfd000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/dwp
	linux-vdso.so.1 =>  (0x00007ffe6fdf7000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f019f504000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f019f202000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f019ee34000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f019f708000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/gnomevfs-df
	linux-vdso.so.1 =>  (0x00007ffcf0b53000)
	libgnomevfs-2.so.0 => /lib64/libgnomevfs-2.so.0 (0x00007fed8b211000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007fed8b00d000)
	libxml2.so.2 => /lib64/libxml2.so.2 (0x00007fed8aca3000)
	libdbus-glib-1.so.2 => /lib64/libdbus-glib-1.so.2 (0x00007fed8aa7b000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007fed8a82b000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007fed8a5db000)
	libssl.so.10 => /lib64/libssl.so.10 (0x00007fed8a369000)
	libcrypto.so.10 => /lib64/libcrypto.so.10 (0x00007fed89f06000)
	libavahi-glib.so.1 => /lib64/libavahi-glib.so.1 (0x00007fed89d02000)
	libavahi-common.so.3 => /lib64/libavahi-common.so.3 (0x00007fed89af5000)
	libavahi-client.so.3 => /lib64/libavahi-client.so.3 (0x00007fed898e4000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007fed896cb000)
	libgconf-2.so.4 => /lib64/libgconf-2.so.4 (0x00007fed8949a000)
	libgthread-2.0.so.0 => /lib64/libgthread-2.0.so.0 (0x00007fed89298000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007fed88f82000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007fed88d5b000)
	libutil.so.1 => /lib64/libutil.so.1 (0x00007fed88b58000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fed8893c000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fed8856e000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fed8836a000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007fed88108000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fed87ef2000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007fed87ccc000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fed879ca000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007fed8762b000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007fed873fa000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007fed871f2000)
	libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007fed86fa5000)
	libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007fed86cbc000)
	libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007fed86ab8000)
	libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007fed86885000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fed8b47a000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007fed86642000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fed8642c000)
	libcap.so.2 => /lib64/libcap.so.2 (0x00007fed86227000)
	librt.so.1 => /lib64/librt.so.1 (0x00007fed8601f000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007fed85e0a000)
	libgcrypt.so.11 => /lib64/libgcrypt.so.11 (0x00007fed85b89000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007fed85984000)
	libdw.so.1 => /lib64/libdw.so.1 (0x00007fed85733000)
	libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007fed85523000)
	libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007fed8531f000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007fed850df000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007fed84eda000)
	libattr.so.1 => /lib64/libattr.so.1 (0x00007fed84cd5000)
	libelf.so.1 => /lib64/libelf.so.1 (0x00007fed84abd000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fed848ad000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/infokey
	linux-vdso.so.1 =>  (0x00007ffc1faf7000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f381b2b2000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f381b680000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/ldns-dane
	linux-vdso.so.1 =>  (0x00007ffe687ca000)
	libpcap.so.1 => /lib64/libpcap.so.1 (0x00007f0538e78000)
	libldns.so.1 => /lib64/libldns.so.1 (0x00007f0538c1f000)
	libcrypto.so.10 => /lib64/libcrypto.so.10 (0x00007f05387bc000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f05385b8000)
	libssl.so.10 => /lib64/libssl.so.10 (0x00007f0538346000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f0537f78000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f0537d62000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f05390b9000)
	libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007f0537b15000)
	libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007f053782c000)
	libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007f0537628000)
	libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007f05373f5000)
	libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007f05371e5000)
	libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007f0536fe1000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f0536dc8000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f0536bac000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f0536985000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f0536723000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/neato
	linux-vdso.so.1 =>  (0x00007ffd92889000)
	libgvc.so.6 => /lib64/libgvc.so.6 (0x00007f6de617e000)
	libltdl.so.7 => /lib64/libltdl.so.7 (0x00007f6de5f74000)
	libxdot.so.4 => /lib64/libxdot.so.4 (0x00007f6de5d6f000)
	libcgraph.so.6 => /lib64/libcgraph.so.6 (0x00007f6de5b59000)
	libpathplan.so.4 => /lib64/libpathplan.so.4 (0x00007f6de5950000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f6de5726000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f6de5510000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f6de520e000)
	libcdt.so.5 => /lib64/libcdt.so.5 (0x00007f6de5007000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f6de4c39000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f6de4a35000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f6de6418000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/pamtohdiff
	linux-vdso.so.1 =>  (0x00007ffe016fe000)
	libnetpbm.so.11 => /lib64/libnetpbm.so.11 (0x00007f681e8b4000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f681e5b2000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f681e1e4000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f681eaf4000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/pmdate
	linux-vdso.so.1 =>  (0x00007ffc565c9000)
	libpcp.so.3 => /lib64/libpcp.so.3 (0x00007f4c77a13000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f4c77645000)
	libssl3.so => /lib64/libssl3.so (0x00007f4c773ec000)
	libnss3.so => /lib64/libnss3.so (0x00007f4c770bd000)
	libnspr4.so => /lib64/libnspr4.so (0x00007f4c76e7f000)
	libsasl2.so.3 => /lib64/libsasl2.so.3 (0x00007f4c76c62000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f4c76a3c000)
	libavahi-common.so.3 => /lib64/libavahi-common.so.3 (0x00007f4c7682f000)
	libavahi-client.so.3 => /lib64/libavahi-client.so.3 (0x00007f4c7661e000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f4c7631c000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f4c76100000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f4c75efc000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f4c77cb4000)
	libnssutil3.so => /lib64/libnssutil3.so (0x00007f4c75ccc000)
	libplc4.so => /lib64/libplc4.so (0x00007f4c75ac7000)
	libplds4.so => /lib64/libplds4.so (0x00007f4c758c3000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f4c756bb000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f4c754a2000)
	libcrypt.so.1 => /lib64/libcrypt.so.1 (0x00007f4c7526b000)
	libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007f4c7501e000)
	libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007f4c74d35000)
	libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007f4c74b02000)
	libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007f4c748fe000)
	libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007f4c746ee000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007f4c7449e000)
	libfreebl3.so => /lib64/libfreebl3.so (0x00007f4c7429b000)
	libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007f4c74097000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f4c73e70000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f4c73c3f000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f4c739dd000)
	libcap.so.2 => /lib64/libcap.so.2 (0x00007f4c737d8000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f4c735c3000)
	libgcrypt.so.11 => /lib64/libgcrypt.so.11 (0x00007f4c73342000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f4c7313d000)
	libdw.so.1 => /lib64/libdw.so.1 (0x00007f4c72eec000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f4c72cd6000)
	libattr.so.1 => /lib64/libattr.so.1 (0x00007f4c72ad1000)
	libelf.so.1 => /lib64/libelf.so.1 (0x00007f4c728b9000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f4c726a3000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f4c72493000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/pstree
	linux-vdso.so.1 =>  (0x00007ffdd87fc000)
	libtinfo.so.5 => /lib64/libtinfo.so.5 (0x00007f6e60f80000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f6e60d59000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f6e6098b000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f6e60729000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f6e60525000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f6e611aa000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f6e60309000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/sgmldiff
	not a dynamic executable
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/ttmkfdir
	linux-vdso.so.1 =>  (0x00007ffc48f50000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007fe1186a4000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fe11848e000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fe118187000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fe117e85000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fe117c6f000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fe1178a1000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fe117691000)
	libpng15.so.15 => /lib64/libpng15.so.15 (0x00007fe117466000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fe118963000)
[jinbean@lnxsrv09 ~]$ ldd /usr/bin/ypdomainname
	linux-vdso.so.1 =>  (0x00007ffd08ae3000)
	libnsl.so.1 => /lib64/libnsl.so.1 (0x00007f644984b000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f644947d000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f6449a65000)



Note:

For the abrt-action-analyze-vulnerability and sgmldiff, 
I got the error message where "not a dynamic executable".
The reason why I got the error message because the programs does not have
proper dynamic libraries to be used by a program or there is no executable permisson.



7. Get a sorted list of every dynamic library that is used by any of the
   commands on your list (omitting duplicates from your list)

Command:

for x in $(ls /usr/bin | awk '(NR-805330751)%251 == 0')

do

ldd /usr/bin/$x

done |

grep -v "not a" |

sed "s/=>.*//" |

sed "s/[(][^)]*[)]//" |

sort -u


Output:

    /lib64/ld-linux-x86-64.so.2 
	libattr.so.1 
	libavahi-client.so.3 
	libavahi-common.so.3 
	libavahi-glib.so.1 
	libblkid.so.1 
	libbz2.so.1 
	libcap.so.2 
	libcdt.so.5 
	libcgraph.so.6 
	libcom_err.so.2 
	libcrypto.so.10 
	libcrypt.so.1 
	libc.so.6 
	libdbus-1.so.3 
	libdbus-glib-1.so.2 
	libdl.so.2 
	libdw.so.1 
	libelf.so.1 
	libexpat.so.1 
	libffi.so.6 
	libfreebl3.so 
	libfreetype.so.6 
	libgcc_s.so.1 
	libgconf-2.so.4 
	libgcrypt.so.11 
	libgio-2.0.so.0 
	libglib-2.0.so.0 
	libgmodule-2.0.so.0 
	libgnomevfs-2.so.0 
	libgobject-2.0.so.0 
	libgpg-error.so.0 
	libgssapi_krb5.so.2 
	libgthread-2.0.so.0 
	libgvc.so.6 
	libk5crypto.so.3 
	libkeyutils.so.1 
	libkrb5.so.3 
	libkrb5support.so.0 
	libldns.so.1 
	libltdl.so.7 
	liblz4.so.1 
	liblzma.so.5 
	libmount.so.1 
	libm.so.6 
	libnetpbm.so.11 
	libnsl.so.1 
	libnspr4.so 
	libnss3.so 
	libnssutil3.so 
	libpathplan.so.4 
	libpcap.so.1 
	libpcp.so.3 
	libpcre.so.1 
	libplc4.so 
	libplds4.so 
	libpng15.so.15 
	libpthread.so.0 
	libresolv.so.2 
	librt.so.1 
	libsasl2.so.3 
	libselinux.so.1 
	libssl3.so 
	libssl.so.10 
	libstdc++.so.6 
	libsystemd.so.0 
	libtinfo.so.5 
	libutil.so.1 
	libuuid.so.1 
	libxdot.so.4 
	libxml2.so.2 
	libz.so.1 
	linux-vdso.so.1


Note:

grep -v "not a" => To delete the case "Not a dynamic executable"

sed "s/=>.*//" => To delete the sentence like "=>  (0x00007ffd7058d000)"

sed "s/[(][^)]*[)]//" => To delete the sentence like "(0x00007f0a24ff3000)" 
                         for the sentence which does not have "=>".

sort -u => To omit duplicates from the list.
