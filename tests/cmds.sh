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
cd .. && pwd
cd .. && pwd


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
#	VARIABLES  																   #
# **************************************************************************** #

### SCMD IN VARIABLE ###
export tmp_test="/bin/echo 1" && $tmp_test
unset tmp_test
export tmp_test="/bin/echo" && $tmp_test 1
unset tmp_test

### VARIABLE SPLITTING ###
export X="  A  B  " && echo "1"$X'2'

export X=" A  B  " && echo "1"$X'2'

export X="A  B  " && echo "1"$X'2'

export X="  A  B " && echo "1"$X'2'

export X="  A  B" && echo "1"$X'2'

export X="  A B  " && echo "1"$X'2'

export X="  AB  " && echo "1"$X'2'

export X="  A  B  " && echo $X'2'

export X="  A  B  " && echo "1"$X

export X="" && echo "1"$X'2'

export X=" " && echo "1"$X'2'

export X="   " && echo "1"$X'2'

export X="  A  B  " && echo ?$X'2'

export X="  A  B  " && echo "1"$X?

export X="  A  B  " && echo "1"$X2?

export test=" * " && touch "$USER * ?eHallo" && echo "$USER "*" ?e"* && rm "$USER * ?eHallo"


# **************************************************************************** #
#	WILDCARDS  																   #
# **************************************************************************** #

touch "   " && ls * | grep "   " && rm "   "

echo "Mak"'e'*'*'
echo "Mak"'e'**
echo ***"Mak"'e'**


# **************************************************************************** #
#	REDIRS  																   #
# **************************************************************************** #

>tmp_std_outfile && ls | grep tmp_std_outfile
rm tmp_std_outfile

"" >tmp_std_outfile && ls | grep tmp_std_outfile
rm tmp_std_outfile

# **************************************************************************** #
#	PIPELINES  																   #
# **************************************************************************** #


# **************************************************************************** #
#	GROUPS  																   #
# **************************************************************************** #

(echo 1 | echo 2 && ((echo 3 | grep 3) | (echo 4 | grep 4)))

# (echo 1 | cat 2 && (sleep 1 | sleep 1)) | (sleep 1 | echo 42 || cat)
# echo 1 | (echo 2 || echo 3 && echo 4) || echo 5 | echo 6


# **************************************************************************** #
#	OPERATORS  																   #
# **************************************************************************** #

### SIMPLE OPERATORS ###
echo 1 && echo 2
cat file_does_not_exist && echo 2

echo 1 || echo 2
cat file_does_not_exist || echo 2

echo 1 && echo 2 && echo 3
echo 1 || echo 2 || echo 3

### OPERATORS WITH PIPELINES ###
echo 1 && echo 2 | echo 3
echo 1 || echo 2 | echo 3

echo 1 && cat file_does_not_exist | echo 3
echo 1 && echo 3 | cat file_does_not_exist
echo 1 || cat file_does_not_exist | echo 3
echo 1 || echo 2 | cat file_does_not_exist
cat file_does_not_exist && echo 2 | echo 3
cat file_does_not_exist || echo 2 | echo 3


echo 1 | echo 2 && echo 3
echo 1 | echo 2 || echo 3

echo 1 | echo 2 && echo 3
echo 1 | echo 2 || echo 3


echo 1 | echo 2 && echo 3 | echo 4
echo 1 | echo 2 || echo 3 | echo 4

echo 1 | echo 2 && echo 3 | echo 4
echo 1 | echo 2 || echo 3 | echo 4


echo 1 | echo 2 | echo 3 && echo 4 | echo 5
echo 1 | echo 2 | echo 3 || echo 4 | echo 5

echo 1 | echo 2 | echo 3 && echo 4 | echo 5
echo 1 | echo 2 | echo 3 || echo 4 | echo 5

# **************************************************************************** #
#	MIX  																       #
# **************************************************************************** #

grep 42 < in | wc -l && ( /bin/echo 1 2 3 4 > out || /bin/echo 2 > out >> out out )


# # Pipe redirected echo
# echo 2 > tmp1 && echo 1 | grep 1

# echo "1\"2"

# ("ec"ho 1) | grep 1

# < test.txt && ls

# echo "'$HOME'"

# echo '"$HOME"'

# export ARG=echo && $ARG 1

# touch tmp99 && touch tmp98 && echo hallo > tmp9* && diff tmp99 tmp98

# export arg=2 && echo $arg

# export arg=5 echo $arg

# echo >/dev/null 1

# echo 1 >/dev/null | grep 1

# echo >/dev/null 1 | echo 2

# grep 2>tmp-error-redirected

# echo 1 > tmp-17 | grep 1 0<tmp-17

# echo $"ARG"

# export ARG="*" && echo $ARG && echo "$ARG"

# echo | ca && est && echo | cat

# > out && echo 1

# echo .*

# (exit)

# echo "*"$tes"t"

# echo 1$tes"t"

# ls 'Make'*

# touch "*1" && echo "*"* && rm "*1"

# touch "a" "aa" && echo *a && rm "a" "aa"

# touch "a" "aa" "aaa" && echo *a*a && rm "a" "aa" "aaa"

# # echo 1 | cat <infile << lim

# # echo 1 | cat <<lim <infile


# (((echo 1)))

# ((echo 1) | (echo 2) | (echo 3 | (echo 4)))

# echo 1 && echo 2 && cat

# touch "   " && ls * | grep "   " && rm "   "

# echo 1 | (grep 1) | cat | (wc -l)
