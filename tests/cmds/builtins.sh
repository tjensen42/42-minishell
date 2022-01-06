# **************************************************************************** #
#	BUILTINS  																   #
# **************************************************************************** #

### ECHO ###
echo test1
echo "echo hallo"
echo echo
echo echo"1"
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
exit 0
exit 10
exit 42
exit 1
exit +1
exit ++1
exit ++12560
exit -1
exit --1
exit -12560
exit --12560
exit 255
exit 1 2
exit 1 2 3
exit A
exit A 2 3
exit "A"
exit "+++"
exit ++++3193912939
exit ++++000
exit "something"
exit x
exit echo
exit exit
exit cd ..
