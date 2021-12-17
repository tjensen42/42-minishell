#include <dirent.h>
#include "expand.h"

bool	expand_token_is_wildcard(t_list *token)
{
	while (token && token_content(token)->flags & TOK_CONNECTED)
	{
		if (!(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
			&& ft_strchr(token_content(token)->string, '*'))
			return (true);
		token = token->next;
	}
	if (token && !(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
		&& ft_strchr(token_content(token)->string, '*'))
		return (true);
	return (false);
}

char	*expand_pattern_get(t_list *token)
{
	char	*wildcard;

	wildcard = ft_strdup("");
	if (wildcard == NULL)
		return (NULL);
	while (token && token_content(token)->flags & TOK_CONNECTED)
	{
		wildcard = expand_wildcard_append_str(wildcard, token);
		if (wildcard == NULL)
			return (NULL);
		token = token->next;
	}
	wildcard = expand_wildcard_append_str(wildcard, token);
	if (wildcard == NULL)
		return (NULL);
	return (wildcard);
}

char	*expand_wildcard_append_str(char *wildcard, t_list *token)
{
	int		i;
	char	*str;

	str = token_content(token)->string;
	if (token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
		return (str_append_str(wildcard, str));
	i = 0;
	while (str[i])
	{
		while (str[i] == '*' && str[i + 1] == '*')
			i++;
		if (str[i] == '*')
			wildcard = str_append_chr(wildcard, WILDCARD);
		else
			wildcard = str_append_chr(wildcard, str[i]);
		if (wildcard == NULL)
			return (NULL);
		i++;
	}
	return (wildcard);
}

char	**expand_files_current_dir(void)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			**file_names;
	char			*fname;

	file_names = NULL;
	dir = opendir("./");
	if (dir == NULL)
		print_error(SHELL_NAME, NULL, NULL, strerror(errno));
	if (dir == NULL)
		return (NULL);
	dirent = readdir(dir);
	while (dirent)
	{
		fname = ft_strdup(dirent->d_name);
		if (fname == NULL || split_append_str(&file_names, fname) == ERROR)
		{
			free(fname);
			ft_free_split(&file_names);
			return (NULL);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (file_names);
}
