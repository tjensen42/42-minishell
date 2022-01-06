# **************************************************************************** #
#	REDIRS  																   #
# **************************************************************************** #

/bin/echo 1 > /dev/null
/bin/echo 1 >> /dev/null

/bin/echo 1 > /dev/null > tmp_redir_out
/bin/echo 1 >> /dev/null >> tmp_redir_out

## PERMISSION DENIES ???

/bin/grep 1 < inputfile
/bin/grep 1 < NO_SUCH_FILE
/bin/grep 1 < inputfile < inputfile
/bin/grep 1 < NO_SUCH_FILE < inputfile

> tmp_std_outfile && echo 1
rm -f tmp_std_outfile

>tmp_std_outfile && ls | grep tmp_std_outfile
rm -f tmp_std_outfile

"" >tmp_std_outfile && ls | grep tmp_std_outfile
rm -f tmp_std_outfile

/bin/echo 1 >/dev/null | /usr/bin/grep 1
/bin/echo 1 >/dev/null | /bin/echo 2
/bin/echo >/dev/null 1 | /usr/bin/grep 1
/bin/echo >/dev/null 1 | /bin/echo 2
