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
		valgrind	--leak-check=full \
        			--show-leak-kinds=all \
        			--track-origins=yes \
        			--verbose \
        			--log-file=tmp-valgrind-out.txt \
					--error-exitcode=42 \
  					../minishell "$line" 2>/dev/null > "$MINISHELL_OUT"
		bash -c "$line" 2>/dev/null > "$BASH_OUT"
		if ! diff -q "$MINISHELL_OUT" "$BASH_OUT" >/dev/null ;
		then
  			echo -ne "\e[0;31mKO\e[m [ $line ]"
			echo $line >> "$DIFF_FILE"
		else
			echo -ne "\e[0;32mOK\e[m"
		fi
		if grep "LEAK SUMMARY" <tmp-valgrind-out.txt >/dev/null ;
		then
			echo -e "\e[0;31m[ valgrind mem-error: $line ]\e[m"
		else
			echo ""
		fi
		((i++))
	fi
done < "$INPUT_FILE"

# Clean all tmp files
rm -f tmp*
