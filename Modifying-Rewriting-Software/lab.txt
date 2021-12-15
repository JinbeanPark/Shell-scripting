Jinbean Park
805330751
Assignment 3. Modifying and rewriting software

1. Laboratory: Installing a small change to a big package

1) Grab the Coreutils 8.29 source code compressed tarball, its signature,
   and GNU keyring at my home directory

wget ftp://ftp.gnu.org/gnu/coreutils/coreutils-8.29.tar.xz

wget ftp://ftp.gnu.org/gnu/coreutils/coreutils-8.29.tar.xz.sig

wget https://ftp.gnu.org/gnu/gnu-keyring.gpg


2) Verify its signature with the GNU keyring by running the shell command

gpg --verify --keyring ./gnu-keyring.gpg coreutils-8.29.tar.xz.sig

I got some of warnings:
gpg: WARNING: options in '/u/cs/ugrad/jinbean/.gnupg/gpg.conf' 
              are not yet active during this run
gpg: WARNING: This key is not certified with a trusted signature!
              There is no indication that the signature belongs to the
              owner.

Primary key fingerprint: 6C37 DC12 121A 5006 BC1D B804 DF6F D971 3060 37D9

I tried verying the keyring by running the gpg command, 
but some of warnings occurred
because I used public key, so it is normal 
that the signature does not belong to the owner.


3) Untar and unzip the tarball

man tar

tar -xJvf coreutils-8.29.tar.xz


4) I made a directory "coreutilsinstall" in my home directory

mkdir ~/coreutilsinstall


5) I went to the coreutils-8.29 I just unzipped and 
   read the INSTALL file

cd coreutils-8.29

emacs INSTALL => Read the explaination and found how to run
                 ./configure with the prefix flag.
cd ../

pwd 

ls -lt => /u/cs/ugrad/jinbean/coreutilsinstall (=absolute path)
=> Check the absolute path to run ./configure

cd coreutils-8.29 
=> Move to coreutils-8.29 to run ./configure

./configure --prefix=/u/cs/ugrad/jinbean/coreutilsinstall


6) Compile and install your copy of Coreutils into 
   a temporary directory of your own.

make => Compile Coreutils into the directory I made (coreutilsinstall)
make install => Install Coreutils into 
                the directory I made (coreutilsinstall)

There was no problem while compiling 
and installing the copy of Coreutils


7) To reproduce the bug on my machine with 
   the unmodified version of coreutils,
   I went to the directory "coreutilsinstall".
   The reason why I went to the directory "coreutilsinstall"
   since I have to use coreutils 8.29 
   and manually runs the executable in this directory.

cd ~/coreutilsinstall/

./bin/ls -aA
=> . .. bin libexec share
=> Printed out four lines with buggy instead of two lines


8) Applying the patch of Bug#30963 Message #10.

cd ~/coreutils-8.29

touch patch_file

emacs patch_file => Copy and Paste the patch of Bug#30963 Message #10

patch -p1 < patch_file

Some of FAILED messages showed up on the screen
Hunk #1 FAILED at 4.
1 out of 1 hunk FAILED -- saving rejects to file NEWS.rej
Hunk #1 FAILED at 575
1 out of 1 hunk FAILED -- saving rejects to file tests/local.mk.rej

patching file NEWS
patching file src/ls.c
patching file tests/local.mk
patching file tests/ls/a-option.sh


9) Typing the command make at the top level of my source tree.

make


10) For each command that gets executed, explain 
    why it needed to be executed

We need to execute the command 'make' to apply 
the cotents of patch file to the coreutils-8.29,
but we do not need to execute the command 'make install'
because we do not need to re-install in the install folder
(=coreutilsInstall).


11) Tested for being fixed the bug

cd src

./ls -aA
=> . .. was not printed out. Therefore patch was applied suceessfully.

ls -aA
=> . .. were still printed out.
