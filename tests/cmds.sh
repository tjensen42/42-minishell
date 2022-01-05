# **************************************************************************** #
#	BUILTINS  																   #
# **************************************************************************** #

### ECHO ###
echo test1
echo "test1 test2"
echo "test1 test2" test3
echo " test1 test2 " 'test3 '
echo test1		test2

echo -n test1
echo -n "test1 test2"
echo -n "test1 test2" test3
echo -n " test1 test2 " 'test3 '
echo -n test1		test2

echo test1 -n
echo "test1 -n"

echo -n -n test1
echo -n -n -n -n -n test1
echo "-n test1 -n test2"
echo "test1 -n test2"

### CD ###
cd "." && pwd
cd ".." && pwd
cd "dir_doesnot_exist" && pwd
# extras
# cd -
# cd

### PWD ###
pwd
"pwd"
pw"d"
pwd test42

### EXPORT ###
export HALLO=42
export HOME=42
export ?=hallo

### UNSET ###


### ENV ###
env | grep DOESNT_EXIST
env | grep HOME
env | grep USER
env | wc -l

### EXIT ###
exit
exit 1
exit 42
exit -1
exit 255
exit 1 2
exit 1 2 3
exit A
exit A 2 3


# **************************************************************************** #
#	SCMD  																   	   #
# **************************************************************************** #

ls
cat cmds.sh
/bin/echo test1

""
"ls"
"cat cmds.sh"
"/bin/echo" test1
""'/bin/'echo test1


# **************************************************************************** #
#	BROKEN SCMD															   	   #
# **************************************************************************** #

"."
.ls
./ls
"./"ls
"./""ls"
"./"''"ls"
lsa
/ls
/ls/
/bin/
/bin/cats
./tester.sh


# **************************************************************************** #
#	VARIABLES  																   #
# **************************************************************************** #

### SIMPLE VARS ###
/bin/echo $?

/bin/echo $HOME
/bin/echo $HOME$USER
/bin/echo $"HOME"$USER
/bin/echo $"HOM"E$USER
/bin/echo $"'HOM'E"$USER
/bin/echo $'HOM'E$USER

/bin/echo $"HOME"
/bin/echo $'HOME'
/bin/echo $
/bin/echo "$"
/bin/echo "$""$"
/bin/echo $"$"
/bin/echo $"42$"
/bin/echo "$"$
/bin/echo $'$'
/bin/echo '$'$

/bin/echo $TESTNOTFOUND
/bin/echo $HOME$TESTNOTFOUND
/bin/echo $TESTNOTFOUND$HOME

/bin/echo ""$?""
/bin/echo " "$?" "
/bin/echo $?"42"
/bin/echo ''$?''"42"
/bin/echo 'HELLO'$?:''"42"

/bin/echo "$?"
/bin/echo '$?'
/bin/echo "'$?'"
/bin/echo '"$?"'

### SCMD IN VARIABLE ###
export tmp_test="/bin/echo 1" && $tmp_test
unset tmp_test
export tmp_test="/bin/echo" && $tmp_test 1
unset tmp_test

### VARIABLE SPLITTING ###
export X="  A  B  " && /bin/echo "1"$X'2'

export X=" A  B  " && /bin/echo "1"$X'2'

export X="A  B  " && /bin/echo "1"$X'2'

export X="  A  B " && /bin/echo "1"$X'2'

export X="  A  B" && /bin/echo "1"$X'2'

export X="  A B  " && /bin/echo "1"$X'2'

export X="  AB  " && /bin/echo "1"$X'2'

export X="  A  B  " && /bin/echo $X'2'

export X="  A  B  " && /bin/echo "1"$X

export X="" && /bin/echo "1"$X'2'

export X=" " && /bin/echo "1"$X'2'

export X="   " && /bin/echo "1"$X'2'

export X="  A  B  " && /bin/echo ?$X'2'

export X="  A  B  " && /bin/echo "1"$X?

export X="  A  B  " && /bin/echo "1"$X2?

export test=" * " && touch "$USER * ?eHallo" && /bin/echo "$USER "*" ?e"* && rm "$USER * ?eHallo"


# **************************************************************************** #
#	REDIRS  																   #
# **************************************************************************** #

/bin/echo 1 > /dev/null
/bin/echo 1 >> /dev/null

/bin/echo 1 > /dev/null > tmp_redir_out
/bin/echo 1 >> /dev/null >> tmp_redir_out

## PERMISSION DENIES ???

/bin/grep 1 < inputfile
/bin/grep 1 < NO_SUCH_FILE
/bin/grep 1 < inputfile < inputfile
/bin/grep 1 < NO_SUCH_FILE < inputfile

> tmp_std_outfile && echo 1
rm -f tmp_std_outfile

>tmp_std_outfile && ls | grep tmp_std_outfile
rm -f tmp_std_outfile

"" >tmp_std_outfile && ls | grep tmp_std_outfile
rm -f tmp_std_outfile

/bin/echo 1 >/dev/null | /usr/bin/grep 1
/bin/echo 1 >/dev/null | /bin/echo 2
/bin/echo >/dev/null 1 | /usr/bin/grep 1
/bin/echo >/dev/null 1 | /bin/echo 2


# **************************************************************************** #
#	PIPELINES  																   #
# **************************************************************************** #

/bin/echo 1 | grep 1
/bin/echo 1 | grep 2

/bin/echo 1 | kaka

# **************************************************************************** #
#	GROUPS  																   #
# **************************************************************************** #

((echo 1) | (echo 2) | (echo 3 | (echo 4)))
echo 1 | (echo 2 || echo 3 && echo 4) || echo 5 | echo 6
echo 1 | (grep 1) | cat | (wc -l)

(/bin/echo 1 | /bin/echo 2 && ((/bin/echo 3 | /bin/echo 3) | (/bin/echo 4 | /bin/echo 4)))

(exit)

# (echo 1 | cat 2 && (sleep 1 | sleep 1)) | (sleep 1 | echo 42 || cat)


# **************************************************************************** #
#	OPERATORS  																   #
# **************************************************************************** #

### SIMPLE OPERATORS ###
/bin/echo 1 && /bin/echo 2
cat file_does_not_exist && /bin/echo 2

/bin/echo 1 || /bin/echo 2
cat file_does_not_exist || /bin/echo 2

/bin/echo 1 && /bin/echo 2 && /bin/echo 3
/bin/echo 1 || /bin/echo 2 || /bin/echo 3

### PIPELINES AFTER OPERATORS ###
/bin/echo 1 && /bin/echo 2 | /bin/echo 3
/bin/echo 1 || /bin/echo 2 | /bin/echo 3

/bin/echo 1 && cat file_does_not_exist | /bin/echo 3
/bin/echo 1 && /bin/echo 3 | cat file_does_not_exist
/bin/echo 1 || cat file_does_not_exist | /bin/echo 3
/bin/echo 1 || /bin/echo 2 | cat file_does_not_exist
cat file_does_not_exist && /bin/echo 2 | /bin/echo 3
cat file_does_not_exist || /bin/echo 2 | /bin/echo 3

### PIPELINES BEFORE OPERATOR ###
/bin/echo 1 | /bin/echo 2 && /bin/echo 3
/bin/echo 1 | /bin/echo 2 || /bin/echo 3

/bin/echo 1 | cat file_does_not_exist && /bin/echo 3
/bin/echo 1 | cat file_does_not_exist || /bin/echo 3
cat file_does_not_exist | /bin/echo 2 && /bin/echo 3
cat file_does_not_exist | /bin/echo 2 || /bin/echo 3
/bin/echo 1 | /bin/echo 2 && cat file_does_not_exist
/bin/echo 1 | /bin/echo 2 || cat file_does_not_exist

### PIPELINES BEFORE AND AFTER OPERATOR ###
/bin/echo 1 | /bin/echo 2 && /bin/echo 3 | /bin/echo 4
/bin/echo 1 | /bin/echo 2 || /bin/echo 3 | /bin/echo 4

/bin/echo 1 | /bin/echo 2 | /bin/echo 3 && /bin/echo 4 | /bin/echo 5
/bin/echo 1 | /bin/echo 2 | /bin/echo 3 || /bin/echo 4 | /bin/echo 5


# **************************************************************************** #
#	WILDCARDS  																   #
# **************************************************************************** #

/usr/bin/printf "%s\\n" * | sort

export ARG="*" && /usr/bin/printf "%s\\n" $ARG | sort

ls *
ls 'test'*
ls "test"*

touch "*1" && echo "*"* && rm "*1"
touch "   " && ls * | grep "   " && rm "   "

touch "a" "aa" && echo *a && rm "a" "aa"
touch "a" "aa" "aaa" && echo *a*a && rm "a" "aa" "aaa"

/bin/echo "Mak"'e'*'*'
/bin/echo "Mak"'e'**
/bin/echo ***"Mak"'e'**
/bin/echo "."*
/bin/echo *"."
/bin/echo *"."*
/bin/echo "*"
/bin/echo '*'

/bin/echo 42 >tmp_out*
rm -f "tmp_out*"

# **************************************************************************** #
#	SYNTAX ERRORS															   #
# **************************************************************************** #

/bin/cat ><
/bin/cat <Makefile >

|
&&
||

/bin/echo 1 && /bin/echo 2 ||
/bin/echo 1 && /bin/echo 2 |
/bin/echo 1 && /bin/echo 2 &&

()

(/bin/echo 1
/bin/echo 1)

(/bin/echo 1))

(/bin/echo 1) (/bin/echo 2)





# **************************************************************************** #
#	MIX  																       #
# **************************************************************************** #

grep 42 < in | wc -l && ( /bin/echo 1 2 3 4 > tmp_out || /bin/echo 2 > tmp_out >> tmp_out tmp_out )
rm -f tmp_out
