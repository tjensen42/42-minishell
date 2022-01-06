INPUT_FILE='input.sh'
NL=$'\n'

i=1
end_of_file=0
while [[ $end_of_file == 0 ]] ;
do
	read -r line
	end_of_file=$?
	if [[ $line == \#* ]] || [[ $line == "" ]] ; then
		if [[ $line == "###"*"###" ]] ; then
			echo -e "\033[0;33m$line\033[m"
		elif [[ $line == "#"* ]] ; then
			echo -e "\033[0;36m$line\033[m"
		fi
		continue
	else
		echo -ne "\033[0;35m$i:\033[m "
		while [[ $end_of_file == 0 ]] && [[ $line != \#* ]] && [[ $line != "" ]] ;
		do
			INPUT+="$line$NL"
			read -r line
			end_of_file=$?
		done
		./minishell <<< "$INPUT" 2>/dev/null >tmp_out_minishell
		exit_minishell=$?
		bash <<< "$INPUT" 2>/dev/null >tmp_out_bash
		exit_bash=$?
		echo -ne "\033[0;34mSTD_OUT:\033[m "
		if ! diff -q tmp_out_minishell tmp_out_bash >/dev/null ;
		then
			echo -ne "\033[0;31mKO" [ ${INPUT:0:30} ... ] "\033[m\t"
		else
			echo -ne "\033[0;32mOK\033[m\t"
		fi
		echo -ne "\033[0;36mEXIT_CODE:\033[m "
		if [[ $exit_minishell != $exit_bash ]] ;
		then
			echo -ne "\033[0;31mKO [ minishell($exit_minishell)  bash($exit_bash) ]\033[m"
		else
			echo -ne "\033[0;32mOK\033[m\t"
		fi
		INPUT=""
		((i++))
		echo ""
	fi
done < "$INPUT_FILE"

# Clean all tmp files
rm -f tmp_*
