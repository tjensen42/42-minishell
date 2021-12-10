#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "printer.h"
#include "env.h"
#include "global.h"
#include "exec.h"
#include "signals.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*minishell_get_line(void);
int		minishell_process_input(char *input);

char	**g_env = NULL;

int	main(int argc, char *argv[])
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	if (env_init() == ERROR)
		return (ERROR);
	if (argc == 2)
		minishell_process_input(argv[1]);
	else
	{
		while (1)
		{
			signal(SIGINT, signal_ctlc);
			termios_change(false);
			input = minishell_get_line();
			if (input == NULL)
			{
				write(1, "\x1b[uexit\n", 9);
				termios_change(true);
				break ;
			}
			minishell_process_input(input);
		}
	}
	rl_clear_history();
	ft_free_split(&g_env);
	return (0);
}

int	minishell_process_input(char *input)
{
	t_list	*l_token;
	t_list	*l_parser;

	signal(SIGINT, SIG_IGN);
	errno = 0;
	l_token = NULL;
	l_parser = NULL;
	l_token = lexer(input);
	if (l_token != NULL)
		l_parser = parser(l_token);
	if (l_token != NULL && l_parser != NULL)
		// printf("return: %d\n", exec_recursive(l_parser));
		exec_recursive(l_parser);
	ft_lstclear(&l_parser, c_cmd_destroy);
	return (0);
}

char *minishell_get_line(void)
{
	char	*input;

	input = readline(PROMPT);
	if (input == NULL)
		return (NULL);
	else if (input[0] != '\0')
		add_history(input);
	rl_on_new_line();
	return (input);
}
