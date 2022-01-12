# **************************************************************************** #
#   PIPELINES                                                                  #
# **************************************************************************** #

/bin/echo 1 | grep 1

/bin/echo 1 | grep 2

ifconfig | grep ":"

ifconfig | grep nothing

cd .. | echo "42"

echo 42 | cat -e

echo 42 | echo no | echo smth | grep 42

echo 42 | echo no | echo smth | grep no

echo 42 | echo no | echo smth | grep smth

/bin/echo 1 | kaka

echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e

/bin/echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e

ls -la ../ | grep "."

unset TEST | cat -e

cat tmp_lol.c | cat > tmp_lol.c
rm -rf tmp_lol.c

/bin/echo 1 > tmp_lol.c
cat tmp_lol.c | cat > tmp_lol.c
rm -rf tmp_lol.c
