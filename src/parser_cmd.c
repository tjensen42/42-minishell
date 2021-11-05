#include "parser.h"

static char **parser_cmd_get(t_list *l_token, int i_text);
static int	parser_cmd_count_text(t_list *l_token);
static int	parser_cmd_count_redir(t_list *l_token);

int	parser_cmd_set(t_c_element *c_element, t_list *l_token)
{
	int 		i_text;
	int 		i_redir;

	c_element->type = PAR_CMD;
	i_text = parser_cmd_count_text(l_token);
	c_element->cmd = parser_cmd_get(l_token, i_text);
	if (c_element->cmd == NULL)
		return (ERROR);
	i_redir = parser_cmd_count_redir(l_token);
	c_element->redirs = parser_get_redirs(l_token, i_redir);
	if (c_element->cmd == NULL)
		return (ERROR);
	c_element->files = parser_get_redir_files(l_token, i_redir);
	if (c_element->cmd == NULL)
		return (ERROR);
	return (0);
}

static char **parser_cmd_get(t_list *l_token, int i_text)
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

static int	parser_cmd_count_redir(t_list *l_token)
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

static int	parser_cmd_count_text(t_list *l_token)
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
