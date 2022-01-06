#!/bin/bash

# INPUT	 / OUTPUT FILES
INPUT_FILE='cmds.sh'
DIFF_FILE='diff_result.sh'

MINISHELL_OUT='tmp-minishell_out'
BASH_OUT='tmp-bash_out'

# Append the actual date, to have a clear seperation between multiple test-runs
echo "" >> "$DIFF_FILE"
echo $(date) >> "$DIFF_FILE"

# Main "tester"
i=1
while read line ;
do
	if [[ $line != \#* ]] && [[ $line != "" ]] ;
	then
		echo -ne "$i: "
  		../minishell "$line" 2>/dev/null > "$MINISHELL_OUT"
		minishell_exit=$?
		bash -c "$line" 2>/dev/null > "$BASH_OUT"
		bash_exit=$?
		if ! diff -q "$MINISHELL_OUT" "$BASH_OUT" >/dev/null ;
		then
  			echo -ne "\033[0;31mKO\033[m [ $line ]"
			echo $line >> "$DIFF_FILE"
		else
			echo -ne "\033[0;32mOK\033[m"
		fi
		if [[ $minishell_exit != $bash_exit ]] ;
		then
			echo "[ exit fail: (minishell: $minishell_exit) (bash: $bash_exit) ]"
			echo $line >> "$DIFF_FILE"
		else
			echo ""
		fi
		((i++))
	fi
done < "$INPUT_FILE"

# Clean all tmp files
rm -f tmp*



##################
# UPGRADES
##################

# unset PATH
# Start Shells without env (env -i bash -c 'echo $HOME $USER')
# lsof -c tests
# ulimit tests....
# testfor redirs // all files created with correct permissions and lsof ...

# HERE_DOC ???
