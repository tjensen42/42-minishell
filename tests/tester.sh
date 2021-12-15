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
		echo -n "$i: "
  		../minishell "$line" > "$MINISHELL_OUT" 2>/dev/null
		bash -c "$line" > "$BASH_OUT" 2>/dev/null
		if ! diff -q "$MINISHELL_OUT" "$BASH_OUT" &>/dev/null;
		then
  			echo -e "\033[0;31mKO\033[m"
			echo $line >> "$DIFF_FILE"
		else
			echo -e "\033[0;32mOK\033[m"
		fi
		((i++))
	fi
done < "$INPUT_FILE"

# Clean all tmp files
rm -f tmp*
