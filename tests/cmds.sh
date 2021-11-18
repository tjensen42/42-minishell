echo 1 || echo 2 | echo 3

echo 1 | (echo 2 || echo 3 && echo 4) || echo 5 | echo 6

# Pipe redirected echo
echo 2 > tmp1 && echo 1 | grep 1

echo "1\"2"

("ec"ho 1) | grep 1

< test.txt && ls

echo "'$HOME'"

echo '"$HOME"'

export ARG=echo && $ARG 1

touch tmp99 && touch tmp98 && echo hallo > tmp9* && diff tmp99 tmp98

export arg=2 && echo $arg

export arg=5 echo $arg

echo >/dev/null 1

echo 1 >/dev/null | grep 1

echo >/dev/null 1 | echo 2

grep 2>tmp-error-redirected

echo 1 > tmp-17 | grep 1 0<tmp-17

echo $"ARG"

export ARG="*" && echo $ARG && echo "$ARG"

echo | ca && est && echo | cat

> out && echo 1

(exit)

# echo 1 | cat <infile << lim

# echo 1 | cat <<lim <infile


(((echo 1)))

((echo 1) | (echo 2) | (echo 3 | (echo 4)))

echo 1 && echo 2 && cat






<in grep 42 | wc -l && (echo "1 2 3" > out 4 || echo 2 >out >>out'out')

< : in : grep : 42 : | : wc : -l : && : ( : echo : 1 2 3 : > : out : 4 : || : echo : 2 : > : out : >> : out + out : )

grep 42 < in | wc -l && ( echo 1 2 3 4 > out || echo 2 > out >> out out )

	P				&&	(P					||	P						)
	P				&&	G





(echo 1 | cat 2 && (sleep 5 | sleep 3)) | (sleep 4 | echo 42 || cat)

(	P			&&			P		)	| (	P				||	P)

				G						|	G

										P

while (brackets left)
	1. Pipelines erstellen
	2. Groups
1. Pipelines erstellen














