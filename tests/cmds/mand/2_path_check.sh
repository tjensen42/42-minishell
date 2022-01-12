# **************************************************************************** #
#   PATH FAILS                                                                 #
# **************************************************************************** #

unset PATH
echo $PATH
cat
ls
echo 1
/bin/echo 42

unset PATH
/bin/echo 42
unset PATH
unset PATH
unset PATH
echo $PATH
cat
ls
echo 1
/bin/echo 42

export PATH=""
echo $PATH
cat
ls
echo 1
/bin/echo 42

export PATH=
echo $PATH
cat
ls
echo 1
/bin/echo 42

export PATH=1
echo $PATH
cat
ls
echo 1
/bin/echo 42

touch tmp_x_file1
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
export PATH=$HOME
echo $PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
unset PATH
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
/bin/echo 42
/bin/rm -f tmp_x_file1
