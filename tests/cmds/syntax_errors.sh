# **************************************************************************** #
#	SYNTAX ERRORS															   #
# **************************************************************************** #

/bin/cat ><
/bin/cat <Makefile >

|
&&
||

/bin/echo 1 && /bin/echo 2 ||
/bin/echo 1 && /bin/echo 2 |
/bin/echo 1 && /bin/echo 2 &&

()

(/bin/echo 1
/bin/echo 1)

(/bin/echo 1))

(/bin/echo 1) (/bin/echo 2)
