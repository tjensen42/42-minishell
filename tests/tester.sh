NL=$'\n'

main() {
	if [[ $1 == "m" ]] ; then
		test_mandatory
	elif [[ $1 == "b" ]] ; then
		test_bonus
	elif [[ $1 == "a" ]] ; then
		test_mandatory
		test_bonus
	else
		echo "usage: bash test.sh [m,b,a]"
	fi
}

test_mandatory() {
	test_from_file "cmds/mand/builtins.sh"
}

test_bonus() {
	test_from_file "cmds/bonus/groups.sh"
}

test_from_file() {
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
			../minishell <<< "$INPUT" 2>/dev/null >tmp_out_minishell
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
				echo -ne "\033[0;31mKO [ minishell($exit_minishell)  bash($exit_bash) ]" [ ${INPUT:0:30} ... ] "\033[m"
			else
				echo -ne "\033[0;32mOK\033[m\t"
			fi
			INPUT=""
			((i++))
			echo ""
		fi
	done < "$1"
}

# Start the tester
main "$@"

# Clean all tmp files
# rm -f tmp_*
