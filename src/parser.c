#include "minishell.h"
#include "parser.h"

t_c_command	*parser_get_command(t_list *l_token)
{
	int 		i_text;
	int 		i_redir;
	t_c_command	*c_command;

	c_command = malloc(sizeof(t_c_command));
	if (c_command == NULL)
		return (NULL);
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
		if (token_content(l_token)->type == TYPE_REDIR)
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
		if (token_content(l_token)->type == TYPE_REDIR_FILE)
		{
			files[i] = ft_strdup(token_content(l_token)->string);
			i++;
		}
		l_token = l_token->next;
	}
	redirs[i] = NULL;
	return (files);
}

t_c_command *parser_get_cmd(t_list *l_token, int i_text)
{
	int 	i;
	char	**cmd;

	cmd = malloc(sizeof((i_text + 1) * sizeof(char *)));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (i < i_text)
	{
		if (token_content(l_token)->type == TYPE_TEXT)
		{
			cmd[i] = ft_strdup(token_content(l_token)->string);
			if (cmd[i] == NULL)
				ft_free_split(&(c_command->cmd));
			if (cmd[i] == NULL)
				return (NULL);
			i++;
		}
		l_token = l_token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	parser_cmd_count_redir(t_list *l_token)
{
	int	i;
	int	type;

	i = 0;
	while (l_token)
	{
		type = token_content(l_token)->type;
		if (type == TYPE_REDIR)
			i++;
		else if (type != TYPE_TEXT && type != TYPE_REDIR_FILE)
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
		if (type == TYPE_TEXT)
			i++;
		else if (type != TYPE_REDIR && type != TYPE_REDIR_FILE)
			break ;
		l_token = l_token->next;
	}
	return (i);
}

int	parser(t_list *l_token)
{
	t_c_command	*c_command;
	t_list		*l_parser;

	l_parser = NULL;
	while (l_token != NULL)
	{
		if (parser_token_is_command(l_token))
		{
			c_command = parser_get_command(l_token);
			if (c_command == NULL)
			{
				parser_command_destroy();
				return (ERROR);
			}
			ft_lstadd_back(&l_parser, ft_lstnew(c_command));
			while (parser_token_is_command(l_token))
				l_token = l_token->next;
		}
		else
		{
			ft_lstadd_back(&l_parser, lexer_get_token(token_content(l_token)->string, token_content(l_token)->type));
			l_token = l_token->next;
		}
	}
}

bool	parser_token_is_command(t_list *token)
{
	int	type;

	type = token_content(token)->type;
	if (type == TYPE_TEXT || type == TYPE_REDIR || type == TYPE_REDIR_FILE)
		return (true);
	return (false);
}
