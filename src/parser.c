#include "minishell.h"
#include "parser.h"

t_c_command *command_content(t_list *command)
{
	return ((t_c_command *)command->content);
}

int	parser_cmd_count_redir(t_list *l_token)
{
	int	i;
	int	type;

	i = 0;
	while (l_token)
	{
		type = token_content(l_token)->type;
		if (type == TOK_REDIR)
			i++;
		else if (type != TOK_TEXT && type != TOK_REDIR_FILE)
			break ;
		l_token = l_token->next;
	}
	return (i);
}

int	parser_cmd_count_text(t_list *l_token)
{
	int	i;
	int	type;

	i = 0;
	while (l_token)
	{
		type = token_content(l_token)->type;
		if (type == TOK_TEXT)
			i++;
		else if (type != TOK_REDIR && type != TOK_REDIR_FILE)
			break ;
		l_token = l_token->next;
	}
	return (i);
}

bool	parser_token_is_command(t_list *token)
{
	int	type;

	if (token == NULL)
		return (false);
	type = token_content(token)->type;
	if (type == TOK_TEXT || type == TOK_REDIR || type == TOK_REDIR_FILE)
		return (true);
	return (false);
}

int	parser_get_type(t_list *token)
{
	if (parser_token_is_command(token))
		return (PAR_CMD);
	else if (token_content(token)->type == TOK_BIN_OP)
	{
		if (token_content(token)->string[0] == '&')
			return (PAR_AND);
		else if (token_content(token)->string[0] == '|')
			return (PAR_OR);
	}
	else if (token_content(token)->type == TOK_PIPE)
		return (PAR_PIPE);
	else if (token_content(token)->type == TOK_BRACKET)
	{
		if (token_content(token)->string[0] == '(')
			return (PAR_O_BRACKET);
		else if (token_content(token)->string[0] == ')')
			return (PAR_C_BRACKET);
	}
	return (ERROR);
}


t_c_command	*parser_get_command(t_list *l_token)
{
	int 		i_text;
	int 		i_redir;
	int 		type;
	t_c_command	*c_command;

	c_command = malloc(sizeof(t_c_command));
	if (c_command == NULL)
		return (NULL);
	type = parser_get_type(l_token);
	if (type != PAR_CMD)
	{
		c_command->type = type;
		c_command->cmd = NULL;
		c_command->redirs = NULL;
		c_command->files = NULL;
		return (c_command);
	}
	c_command->type = PAR_CMD;
	i_text = parser_cmd_count_text(l_token);
	c_command->cmd = parser_get_cmd(l_token, i_text);
	if (c_command->cmd == NULL)
		return (NULL);
	i_redir = parser_cmd_count_redir(l_token);
	c_command->redirs = parser_get_redirs(l_token, i_redir);
	if (c_command->cmd == NULL)
		return (NULL);
	c_command->files = parser_get_redir_files(l_token, i_redir);
	if (c_command->cmd == NULL)
		return (NULL);
	return (c_command);
}

char	**parser_get_redirs(t_list *l_token, int i_redir)
{
	int		i;
	char	**redirs;

	redirs = malloc((i_redir + 1) * sizeof(char *));
	if (redirs == NULL)
		return (NULL);
	i = 0;
	while (i < i_redir)
	{
		if (token_content(l_token)->type == TOK_REDIR)
		{
			redirs[i] = ft_strdup(token_content(l_token)->string);
			i++;
		}
		l_token = l_token->next;
	}
	redirs[i] = NULL;
	return (redirs);
}

char	**parser_get_redir_files(t_list *l_token, int i_redir)
{
	int		i;
	char	**files;

	files = malloc((i_redir + 1) * sizeof(char *));
	if (files == NULL)
		return (NULL);
	i = 0;
	while (i < i_redir)
	{
		if (token_content(l_token)->type == TOK_REDIR_FILE)
		{
			files[i] = ft_strdup(token_content(l_token)->string);
			i++;
		}
		l_token = l_token->next;
	}
	files[i] = NULL;
	return (files);
}

char **parser_get_cmd(t_list *l_token, int i_text)
{
	int 	i;
	char	**cmd;

	cmd = malloc((i_text + 1) * sizeof(char *));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (i < i_text)
	{
		if (token_content(l_token)->type == TOK_TEXT)
		{
			cmd[i] = ft_strdup(token_content(l_token)->string);
			if (cmd[i] == NULL)
				ft_free_split(&cmd);
			if (cmd[i] == NULL)
				return (NULL);
			i++;
		}
		l_token = l_token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	parser(t_list *l_token)
{
	t_c_command	*c_command;
	t_list		*l_command;

	l_command = NULL;
	while (l_token != NULL)
	{
		if (parser_token_is_command(l_token))
		{
			c_command = parser_get_command(l_token);
			if (c_command == NULL)
			{
				// parser_command_destroy();
				return (ERROR);
			}
			ft_lstadd_back(&l_command, ft_lstnew(c_command));
			while (l_token && parser_token_is_command(l_token))
				l_token = l_token->next;
		}
		else
		{
			c_command = parser_get_command(l_token);
			if (c_command == NULL)
			{
				//parser_command_destroy();
				return (ERROR);
			}
			ft_lstadd_back(&l_command, ft_lstnew(c_command));
			l_token = l_token->next;
		}
	}
	parser_printer(l_command);
	return (0);
}

void	parser_printer(t_list *l_command)
{
	int i;
	int type;

	while (l_command)
	{
		if (command_content(l_command)->type == PAR_CMD)
		{
			//printf("cmd:\t");
			i = 0;
			while (command_content(l_command)->cmd[i])
			{
				if (i == 0)
					printf("\033[0;33m%s \033[m", command_content(l_command)->cmd[i]);
				else
					printf("\033[0;32m%s \033[m", command_content(l_command)->cmd[i]);
				i++;
			}
			i = 0;
			while (command_content(l_command)->redirs[i])
			{
				printf("\033[0;36m%s \033[m", command_content(l_command)->redirs[i]);
				printf("\033[0;34m%s \033[m", command_content(l_command)->files[i]);
				i++;
			}
		}
		else
		{
			type = command_content(l_command)->type;
			if (type == PAR_AND)
				printf("\033[0;31m&& \033[m");
			else if (type == PAR_OR)
				printf("\033[0;31m|| \033[m");
			else if (type == PAR_PIPE)
				printf("\033[0;31m| \033[m");
			else if (type == PAR_O_BRACKET)
				printf("\033[0;31m( \033[m");
			else if (type == PAR_C_BRACKET)
				printf("\033[0;31m) \033[m");
			else
				printf("DEAD ");
		}
		l_command = l_command->next;
	}
	printf("\n");
}
