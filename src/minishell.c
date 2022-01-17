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
void	minishell_process_input(char *input);

char	**g_env = NULL;

int	main(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	if (env_init() == ERROR)
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, signal_ctlc);
		termios_change(false);
		input = minishell_get_line();
		if (input == NULL)
		{
			if (isatty(STDERR_FILENO))
				ft_putendl_fd("exit", STDERR_FILENO);
			termios_change(true);
			break ;
		}
		minishell_process_input(input);
	}
	rl_clear_history();
	if (g_env)
		ft_free_split(&g_env);
	exit(exit_status_get());
}

void	minishell_process_input(char *input)
{
	t_list	*l_token;
	t_list	*l_parser;

	signal(SIGINT, SIG_IGN);
	errno = 0;
	l_token = NULL;
	l_parser = NULL;
	l_token = lexer(input);
	free(input);
	if (l_token != NULL)
		l_parser = parser(l_token);
	if (l_token != NULL && l_parser != NULL)
		exec_recursive(l_parser, false, l_parser);
	if (l_parser != NULL)
		ft_lstclear(&l_parser, c_cmd_destroy);
	else if (l_token != NULL)
		ft_lstclear(&l_token, c_token_destroy);
}

char	*minishell_get_line(void)
{
	char	*input;
	char	*prompt;

	prompt = env_get_value("PS1");
	if (prompt == NULL)
		prompt = PROMPT;
	if (isatty(STDIN_FILENO))
		input = readline(prompt);
	else
		input = minishell_get_next_line(STDIN_FILENO);
	if (input == NULL)
		return (NULL);
	else if (input && input[0])
		add_history(input);
	return (input);
}
