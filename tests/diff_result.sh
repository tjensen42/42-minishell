
Thu Nov 4 18:31:17 CET 2021
echo 1 || echo 2 | echo 3
echo 1 | (echo 2 || echo 3 && echo 4) || echo 5 | echo 6
echo 2 > tmp1 && echo 1 | grep 1
echo "1"2"
("ec"ho 1) | grep 1
< test.txt && ls
echo "'$HOME'"
echo '"$HOME"'
ARG=echo && $ARG 1
touch tmp99 && touch tmp98 && echo hallo > tmp98 tmp99 && diff tmp99 tmp98
arg=2 && echo $arg
arg=5 echo $arg
echo >/dev/null 1
echo 1 >/dev/null | grep 1
echo >/dev/null 1 | echo 2
grep 2>tmp-error-redirected
echo 1 > tmp-17 | grep 1 0<tmp-17
