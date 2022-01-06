# **************************************************************************** #
#	GROUPS  																   #
# **************************************************************************** #

((echo 1) | (echo 2) | (echo 3 | (echo 4)))
echo 1 | (echo 2 || echo 3 && echo 4) || echo 5 | echo 6
echo 1 | (grep 1) | cat | (wc -l)

(/bin/echo 1 | /bin/echo 2 && ((/bin/echo 3 | /bin/echo 3) | (/bin/echo 4 | /bin/echo 4)))

(exit)

# (echo 1 | cat 2 && (sleep 1 | sleep 1)) | (sleep 1 | echo 42 || cat)
