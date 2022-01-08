# **************************************************************************** #
#   PATH FAILS                                                                 #
# **************************************************************************** #

unset PATH
echo $PATH
cat
ls
/bin/ls
echo 1

unset PATH
/bin/ls
unset PATH
unset PATH
unset PATH
echo $PATH
cat
ls
/bin/ls
echo 1

export PATH=""
echo $PATH
cat
ls
/bin/ls
echo 1

export PATH=
echo $PATH
cat
ls
/bin/ls
echo 1

export PATH=1
echo $PATH
cat
ls
/bin/ls
echo 1

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
/bin/ls
/bin/rm -f tmp_x_file1
