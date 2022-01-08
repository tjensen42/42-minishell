# **************************************************************************** #
#   WILD                                                                       #
# **************************************************************************** #

sleep 0 | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat

grep 1 < filedoesnotexist | echo 1 | grep 1 | head -1 | cat

grep 1 < filedoesnotexist | echo 1 | grep 1 > tmp_out | head -1 | cat
cat tmp_out
rm -f tmp_out

/bin/echo 'echo 42' | cat <tmp_file
/bin/echo file > tmp_file
/bin/echo 'echo 42' | cat <tmp_file
rm -f tmp_file

cat /dev/urandom | head -1 > tmp_out
bash -c "[ -s tmp_out ] && echo nice"
/bin/echo $?
rm -f tmp_out

cat /dev/urandom | head -1 | wc -l

cat /dev/null | head -1

cat nofile | echo 42 | grep 42

echo 1 > tmp_out
echo 42 | grep 42 < tmp_out
echo 42 | grep 1 < tmp_out
rm -f tmp_out

/usr/bin/env -i bash -c "env" | wc -l

/bin/echo '\1$42' > tmp_redir_out
ls -la | grep tmp_redir_out | awk '{print $1 $2}'
cat -e tmp_redir_out
rm tmp_redir_out

export test=" arg1 arg2 "
echo 'echo $1' > tmp_test_sh
bash tmp_test_sh $test
echo 'echo $2' > tmp_test_sh
bash tmp_test_sh $test
rm -f tmp_test_sh

export pipe_var=1 | echo $pipe_var
echo $pipe_var

echo $PATH
echo $HOME
unset PATH HOME
echo $PATH
echo $HOME

cat /dev/urandom | lsof -c cat | wc -l

echo "env | /usr/bin/wc -l" | /usr/bin/env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo "ls" | /usr/bin/env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?

echo "unset PATH" | /usr/bin/env -i $MINISHELL_PATH"/"$EXECUTABLE
echo $?
