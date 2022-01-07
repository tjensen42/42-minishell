# **************************************************************************** #
#   PATH FAILS                                                                 #
# **************************************************************************** #

unset PATH
echo $PATH
cat
ls
echo 1

unset PATH
unset PATH
unset PATH
unset PATH
echo $PATH
cat
ls
echo 1

export PATH=""
echo $PATH
cat
ls
echo 1

export PATH=
echo $PATH
cat
ls
echo 1

export PATH=1
echo $PATH
cat
ls
echo 1

touch tmp_x_file1
tmp_x_file1
echo $?
./tmp_x_file1
echo $?
export PATH=$PWD
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
rm -f tmp_x_file1
