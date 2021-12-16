### VARIABLES ###
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

export test=" * " && touch "$USER * ?eHallo" && echo "$USER "*" ?e"* && rm "$USER * ?eHallo"

echo "Mak"'e'*'*'


# echo 1 || echo 2 | echo 3

# echo 1 | (echo 2 || echo 3 && echo 4) || echo 5 | echo 6

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

# env -i bash --noprofile --norc


# <in grep 42 | wc -l && (echo "1 2 3" > out 4 || echo 2 >out >>out'out')

# < : in : grep : 42 : | : wc : -l : && : ( : echo : 1 2 3 : > : out : 4 : || : echo : 2 : > : out : >> : out + out : )


# grep 42 < in | wc -l && ( /bin/echo 1 2 3 4 > out || /bin/echo 2 > out >> out out )

# 	P				&&	(P					||	P						)
# 	P				&&	G


# (echo 1 | cat 2 && (sleep 1 | sleep 1)) | (sleep 1 | echo 42 || cat)

# (	P			&&		(	P	)	)	| (	P				||	P)
# (	P			&&			G			| (	P				||	P)
# 				G						|	G
# 										P

# while (brackets left)
# 	1. Pipelines erstellen
# 	2. Groups
# 1. Pipelines erstellen




# echo 1 | (grep 1) | cat | (wc -l)









