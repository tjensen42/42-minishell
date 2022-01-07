#!/bin/bash

MINISHELL_PATH=../

NL=$'\n'
TAB=$'\t'

TEST_COUNT=0
TEST_KO_OUT=0
TEST_KO_ERR=0
TEST_KO_EXIT=0

main() {
	if [[ ! -f $MINISHELL_PATH/minishell ]] ; then
		echo -e "\033[0;31m# **************************************************************************** #"
		echo "#    MINISHELL NOT COMPILED                                                    #"
		echo "#    TRY TO COMPILE ...                                                        #"
		echo -e "# **************************************************************************** #\033[m"
		make -C $MINISHELL_PATH
	fi
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
	print_stats
}

test_mandatory() {
	FILES="cmds/mand/*"
	for file in $FILES
	do
		test_from_file $file
	done
}

test_bonus() {
	FILES="cmds/bonus/*"
	for file in $FILES
	do
		test_from_file $file
	done
}

print_stats() {
	echo -e "\n# **************************************************************************** #"
	echo "#    RESULT                                                                    #"
	echo "# **************************************************************************** #"
	printf "\033[0;35m%-4s\033[m" "$TEST_COUNT:"
	echo -ne "\033[0;34mSTD_OUT:\033[m "
	if [[ $TEST_KO_OUT == 0 ]] ; then
		echo -ne "\033[0;32m✓ \033[m  "
	else
		echo -ne "\033[0;31m$TEST_KO_OUT / $TEST_COUNT\033[m  "
	fi
	echo -ne "\033[0;36mEXIT_CODE:\033[m "
	if [[ $TEST_KO_EXIT == 0 ]] ; then
		echo -ne "\033[0;32m✓ \033[m  "
	else
		echo -ne "\033[0;31m$TEST_KO_EXIT / $TEST_COUNT\033[m  "
	fi
	echo -ne "\033[0;36mSTD_ERR:\033[m "
	if [[ $TEST_KO_ERR == 0 ]] ; then
		echo -e "\033[0;32m✓ \033[m"
	else
		echo -e "\033[0;31m$TEST_KO_ERR / $TEST_COUNT\033[m"
	fi
}

test_from_file() {
	IFS=''
	i=1
	end_of_file=0
	while [[ $end_of_file == 0 ]] ;
	do
		read -r line
		end_of_file=$?
		if [[ $line == \#* ]] || [[ $line == "" ]] ; then
			# if [[ $line == "###"[[:blank:]]*[[:blank:]]"###" ]] ; then
			# 	echo -e "\033[0;33m$line\033[m"
			if [[ $line == "#"[[:blank:]]*[[:blank:]]"#" ]] ; then
				echo -e "\033[0;33m$line\033[m" | tr '\t' '    '
			fi
			continue
		else
			printf "\033[0;35m%-4s\033[m" "$i:"
			while [[ $end_of_file == 0 ]] && [[ $line != \#* ]] && [[ $line != "" ]] ;
			do
				INPUT+="$line$NL"
				read -r line
				end_of_file=$?
			done
			$MINISHELL_PATH/minishell <<< "$INPUT" 2>tmp_err_minishell >tmp_out_minishell
			exit_minishell=$?
			bash <<< "enable -n .$NL$INPUT" 2>tmp_err_bash >tmp_out_bash
			exit_bash=$?
			echo -ne "\033[0;34mSTD_OUT:\033[m "
			if ! diff -q tmp_out_minishell tmp_out_bash >/dev/null ;
			then
				echo -ne "\033[0;31mKO" [ \"${INPUT:0:15}\" ... ] "\033[m  " | tr '\n' ' '
				((TEST_KO_OUT++))
			else
				echo -ne "\033[0;32mOK\033[m  "
			fi
			echo -ne "\033[0;36mEXIT_CODE:\033[m "
			if [[ $exit_minishell != $exit_bash ]] ;
			then
				echo -ne "\033[0;31mKO [ minishell($exit_minishell)  bash($exit_bash) ]" [ \"${INPUT:0:15}\" ... ] "\033[m  " | tr '\n' ' '
				((TEST_KO_EXIT++))
			else
				echo -ne "\033[0;32mOK\033[m  "
			fi
			echo -ne "\033[0;36mSTD_ERR:\033[m "
			# tmp_err_minishell=`cat tmp_err_minishell | wc -l | tr -d ' '`
			# tmp_err_bash=`cat tmp_err_bash | wc -l | tr -d ' '`
			if [[ -s tmp_err_minishell && ! -s tmp_err_bash ]] || [[ ! -s tmp_err_minishell && -s tmp_err_bash ]] ;
			then
				echo -ne "\033[0;31mKO" "[ \"${INPUT:0:15}\" ... ]" "\033[m  " |  tr '\n' ' '
				((TEST_KO_ERR++))
			else
				echo -ne "\033[0;32mOK\033[m  "
			fi
			INPUT=""
			((i++))
			((TEST_COUNT++))
			echo ""
		fi
	done < "$1"
}

# Start the tester
main "$@"

# Clean all tmp files
rm -f tmp_*
