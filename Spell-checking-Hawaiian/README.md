
Jinbean Park
805330751
Assignment2 - Laboratory: Spell-checking Hawaiian

man sort
sort /usr/share/dict/words > words  
=> It didn't give the correct order of words.

rm words
export LC_ALL='C'
sort /usr/share/dict/words > words 
=> It gave the correct order of words.

man wget
wget http://web.cs.ucla.edu/classes/winter20/cs35L/assign/assign2.html

1) tr -c 'A-Za-z' '[\n*]' < assign2.html
=> The above command replace non-alphabetic characters with new line (=\n)
   because tr -c SET1 SET2 command replace the character 
   that does not belong to SET1 with SET2

2) tr -cs 'A-Za-z' '[\n*]' < assign2.html
=> The above command replace non-alphabetic characters with new line (=\n)
   and replace each repeated character
   with a single occurrence of that character 
   because of the option -s squeezes the repeated things.

3) tr -cs 'A-Za-z' '[\n*]' | sort < assign2.html 
   => It didn't show the correct output.
   tr -cs 'A-Za-z' '[\n*]' < assign2.html | sort 
   => It showed the correct output.
=> It shows the same output with using the command
   tr -cs 'A-Za-z' '[\n*]' < assign2.html,
   but only difference is
   it shows the alphabetically sorted output 
   because the sort command sorts the output alphabetically.

4) tr -cs 'A-Za-z' '[\n*]' < assign2.html | sort -u
=> It shows the output deleting the duplicated word on the above output 
   because the sort option of -u deletes the duplicated words.

5) tr -cs 'A-Za-z' '[\n*]' < assign2.html | sort -u | comm - words
=> The output shows three-column output.
   The first column displays lines unique to the above output,
   and the second column displays lines unique to File "words",
   and the third column displays lines common to both files.

6) tr -cs 'A-Za-z' '[\n*]' < assign2.html | sort - u | comm -23 - words
=> The output shows only first-column from the above output 
   because the option -23 means suppressing the column second and third.
   In other words, the output shows the only the alphabetic sorted lines
   that are unique to assign2.html,
   so we can use the above command for checking 
   whether the words in assign2.html are exist 
   in English dictionary or not.


1) Use Wget to obtain the copy of "Hawaiian to English" web page
wget https://www.mauimapp.com/moolelo/hwnwdshw.htm

#!/bin/bash

2) Remove all instance of '?', '<u>', '</u>'
cat hwnwdshw.htm | sed -E 's/\?|<u>|<\/u>//g' |

3) Remove the lines from <!DOCTYPE html to </font></td> in first part
sed '/<!DOCTYPE/,/\/font><\/td>/d' |

4) Remove the lines from 1st to 3rd.
sed '1,3 d' |

5) Remove the lines from </table> to </html> in last part
sed '/<\/table/,/html>/d' |

6) Remove every tags
sed 's/<[^>]*>'//g |

7) Remove every white spaces located on left side
tr -d '[:blank:]' |

8) Replace ` with '
sed "s/\`/\'/g" |

9) Change Uppercase to Lowercase
tr '[:upper:]' '[:lower:]' |

10) Squeeze the newlines
tr -s '\n' |

11) Delete the words containing non-Hawaiian letters
sed "/[^pk\'mnwlhaeiou]/d" |

12) Sort list of words and remove the duplicated words
sort -u

13) Create the script file "buildwords" 
    and change the mode to execute it
touch buildwords
chmod +x buildwords

14) Put the commands into the buildwords.
Emacs
C-x C-f buildwords
sed -E 's/\?|<u>|<\/u>//g' |
sed '/<!DOCTYPE/,/\/font><\/td>/d' |
sed '1,3 d' |
sed '/<\/table/,/html>/d' |
sed 's/<[^>]*>'//g | tr -d '[:blank:]' |
sed "s/\`/\'/g" |
tr '[:upper:]' '[:lower:]' |
tr -s '\n' |
sed "/[^pk\'mnwlhaeiou]/d" |
sort -u

15) Make the simple Hawaiian dictionary

cat hwnwdshw.htm | ./buildwords > hwords

16) Check the spelling of Hawaiian 
    by deriving a shell command HAWAIIANCHECKER

cat hwords | tr -cs "pk\'mnwlhaeiou" "[\n*]" |
    sort -u | comm -23 - hwords | wc -w

Output: 0

17) Check the number of distinct misspelled words 
    on very web page using ENGLISHCHECKER

cat assign2.html | tr -cs 'A-Za-z' '[\n*]' |
    tr '[:upper:]' '[:lower:]' | sort -u |
    comm -23 - words > misEng
    wc -w < misEng

Output: 48

18) Check the number of distinct misspelled words 
    on very web page using HAWAIIANCHECKER

cat assign2.html | tr -cs "pk\'mnwlhaeiou" "[\n*]" |
    tr '[:upper:]' '[:lower:]' | sort -u |
    comm -23 - hwords > misHaw
    wc -w < misHaw

Output: 235

19) Check the misspelled English but not as Hawaiian

cat misEng | tr -cs "pk\'mnwlhaeiou" "[\n*]" |
    tr '[:upper:]' '[:lower:]' | sort -u |
    comm -12 - hwords > misEngNhaw
    wc -w < misEngNhaw

output: 5
Example:
ke
la
name
po
wiki

20) Check the misspelled Hawaiian but not as English

cat misHaw | tr -cs 'A-Za-z' '[\n*]' |
    tr '[:upper:]' '[:lower:]' | sort -u |
    comm -12 - words > misHawNeng
    wc -w < misHawNeng

output: 121
a
ail
ain
ake
al
ale
alen
all
alone
amp
ample
an
anno
aph
aul
awk
e
ea
ee
el
em
emp
en
eon
ep
epa
ew
h
ha
han
hap
hawaii
he
hei
hell
hen
hi
hin
ho
home
hw
i
ia
ie
il
ile
in
io
ion
iou
k
kin
l
lan
le
lea
li
like
line
link
ll
ln
lo
look
lowe
lu
m
ma
mail
main
mall
me
mean
men
mi
ml
mo
mu
n
ne
nee
newline
non
nu
num
o
ol
om
on
one
op
ope
open
owe
own
p
pe
pell
plain
plea
pu
u
ui
ula
ule
ull
ume
ump
un
uni
up
w
wa
wan
we
wh
wha
when
wi
will
wo
