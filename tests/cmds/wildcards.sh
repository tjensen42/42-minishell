# **************************************************************************** #
#	WILDCARDS  																   #
# **************************************************************************** #

/usr/bin/printf "%s\\n" * | sort

export ARG="*" && /usr/bin/printf "%s\\n" $ARG | sort

ls *
ls 'test'*
ls "test"*

touch "*1" && echo "*"* && rm "*1"
touch "   " && ls * | grep "   " && rm "   "

touch "a" "aa" && echo *a && rm "a" "aa"
touch "a" "aa" "aaa" && echo *a*a && rm "a" "aa" "aaa"

/bin/echo "Mak"'e'*'*'
/bin/echo "Mak"'e'**
/bin/echo ***"Mak"'e'**
/bin/echo "."*
/bin/echo *"."
/bin/echo *"."*
/bin/echo "*"
/bin/echo '*'

/bin/echo 42 >tmp_out*
rm -f "tmp_out*"
