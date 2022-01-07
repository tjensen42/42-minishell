# **************************************************************************** #
#   WILDCARDS                                                                  #
# **************************************************************************** #

/usr/bin/printf "%s\n" * | sort

export ARG="*"
/usr/bin/printf "%s\n" $ARG | sort

ls *
ls 'test'*
ls "test"*

touch "*1"
echo "*"*
rm "*1"

touch "   "
ls * | grep "   "
rm "   "

touch "a" "aa"
echo *a
rm "a" "aa"

touch "a" "aa" "aaa"
echo *a*a
rm "a" "aa" "aaa"

/bin/echo "Mak"'e'*'*'
/bin/echo "Mak"'e'**
/bin/echo ***"Mak"'e'**
/bin/echo "."*
/bin/echo *"."
/bin/echo *"."*
/bin/echo "*"
/bin/echo '*'

/bin/echo Minishe*l
/bin/echo minishe*l

touch minishelxxxl
/bin/echo minishe*l
/bin/echo minishel*l
/bin/echo minishelxxx*l
/bin/echo minishel*xxx*l
rm minishelxxxl

touch tmp_out
/bin/echo 42 >tmp_o*t*
rm -f "tmp_out*"

touch tmp_out1
touch tmp_out2
/bin/echo 42 >tmp_out*
rm -f "tmp_out*"
