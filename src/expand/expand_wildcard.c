#include <dirent.h>
#include "expand.h"

#define WILDCARD	 -1

static char **expand_fname_get(void);
static bool expand_token_is_wildcard(t_list *token);

static int count_dups(char *str);
static int	expand_wildcard_token(t_list *token);

static bool	expand_wildcard_match_fname(char *wildcard, char *fname);

static char	*expand_wildcard_get(t_list *token);
static char	*expand_wildcard_append_str(char *wildcard, t_list *token);

int	expand_wildcard(t_c_scmd *c_scmd)
{
	t_list	*iter;

	iter = c_scmd->l_argv;
	while (iter)
	{
		if (expand_token_is_wildcard(iter))
			if (expand_wildcard_token(iter) == ERROR)
				return (ERROR);
		while (token_content(iter)->flags & TOK_CONNECTED)
			iter = iter->next;
		iter = iter->next;
	}
	iter = c_scmd->l_redir;
	while (iter)
	{
		if (expand_token_is_wildcard(iter))
			if (expand_wildcard_token(iter) == ERROR)
				return (ERROR);
		while (token_content(iter)->flags & TOK_CONNECTED)
			iter = iter->next;
		iter = iter->next;
	}
	return (0);
}

static bool expand_token_is_wildcard(t_list *token)
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

static int	expand_wildcard_token(t_list *token)
{
	int		i;
	char	*wildcard;
	char	**fname;
	t_list	*new_token;
	t_list	*l_wildcards;

	fname = expand_fname_get();
	if (fname == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM);
		return (ERROR);
	}
	l_wildcards = NULL;
	wildcard = expand_wildcard_get(token);
	if (wildcard == NULL)
	{
		ft_free_split(&fname);
		return (ERROR);
	}
	i = 0;
	while (fname[i])
	{
		if (expand_wildcard_match_fname(wildcard, fname[i]))
		{
			new_token = token_create(ft_strdup(fname[i]), token_content(token)->flags); // strdup protec
			if (new_token == NULL)
			{
				ft_free_split(&fname);
				free(wildcard);
			}
			token_content(new_token)->flags &= ~(TOK_CONNECTED | TOK_D_QUOTE | TOK_S_QUOTE);
			ft_lstadd_back(&l_wildcards, new_token);
		}
		i++;
	}
	while (l_wildcards)
	{
		printf("%s\n", token_content(l_wildcards)->string);
		l_wildcards = l_wildcards->next;
	}
	free(wildcard);
	ft_free_split(&fname);
	return (0);
}

// static bool	expand_wildcard_match_fname(char *wildcard, char *fname)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (wildcard[i])
// 	{
// 		if (wildcard[i] == WILDCARD)
// 		{
// 			i++;
// 			if (wildcard[i] == '\0')
// 				return (true);
// 			while (fname[j] && fname[j] != wildcard[i])
// 				j++;
// 			if (fname[j] == '\0')
// 				return (false);
// 			if (count_dups(&wildcard[i]) > count_dups(&fname[j]))
// 				return (false);
// 			i += count_dups(&wildcard[i]);
// 			j += count_dups(&fname[j]);
// 		}
// 		else
// 		{
// 			if (wildcard[i] != fname[j])
// 				return (false);
// 			i++;
// 			j++;
// 			if (wildcard[i] == '\0' && fname[j] == '\0')
// 				return (true);
// 		}
// 	}
// 	return (false);
// }

// static int count_dups(char *str)
// {
// 	int i;
// 	int count;

// 	i = 0;
// 	count = 0;
// 	while (str[i] == str[i + 1])
// 	{
// 		count++;
// 		i++;
// 	}
// 	return (count);
// }









static char	*expand_wildcard_get(t_list *token)
{
	int 	i;
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

static char	*expand_wildcard_append_str(char *wildcard, t_list *token)
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

static char **expand_fname_get(void)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			**paths;
	char			*dir_name;

	paths = NULL;
	dir = opendir("./");
	if (dir == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, strerror(errno));
		return (NULL);
	}
	dirent = readdir(dir);
	while (dirent)
	{
		dir_name = ft_strdup(dirent->d_name);
		if (dir_name == NULL || split_append_str(&paths, dir_name) == ERROR)
		{
			ft_free_split(&paths);
			return (NULL);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (paths);
}



// static bool	expand_fname_is_wild(char *fname, t_list *token)
// {
// 	int		i;
// 	int		j;
// 	char	*wildcard;
// 	bool	quoted;

// 	j = 0;
// 	while (token)
// 	{
// 		quoted = false;
// 		if (token_content(token)->flags & (TOK_S_QUOTE | TOK_D_QUOTE))
// 			quoted = true;
// 		i = 0;
// 		wildcard = token_content(token)->string;
// 		while (wildcard && wildcard[i])
// 		{
// 			while (!quoted && wildcard[i] == '*' && wildcard[i + 1] == '*')
// 				i++;
// 			if (!quoted && wildcard[i] == '*')
// 				i++;
// 			// printf("%d\n", i);
// 			while (wildcard[i] && fname[j] && fname[j] != wildcard[i])
// 				j++;
// 			if (fname[j] != wildcard[i])
// 				return (false);
// 			while (wildcard[i] && wildcard[i] == fname[j]
// 					&& (quoted || wildcard[i] != '*'))
// 			{
// 				i++;
// 				j++;
// 			}
// 			i++;
// 		}
// 		if (token_content(token)->flags & TOK_CONNECTED)
// 			token = token->next;
// 		else
// 			token = NULL;
// 	}
// 	return (true);
// }





static bool	expand_wildcard_match_fname(char *wildcard, char *fname)
{
	int		i;
	char	*shifted_fname;
	char	**splitted;

	splitted = ft_split(wildcard, WILDCARD);
	if (splitted == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	shifted_fname = fname;
	i = 0;
	while (splitted[i])
	{
		shifted_fname = ft_strnstr(shifted_fname, splitted[i], ft_strlen(shifted_fname));
		if (shifted_fname == NULL)
			return (false);
		shifted_fname += ft_strlen(splitted[i]);
		i++;
	}
	if (wildcard[0] != WILDCARD)
	{
		if (ft_strncmp(fname, splitted[0], ft_strlen(splitted[0])) != 0)
			return (false);
	}
	if (wildcard[ft_strlen(wildcard) - 1] != WILDCARD)
	{
		if (ft_strncmp(fname + ft_strlen(fname) - ft_strlen(splitted[i - 1]), splitted[i - 1], ft_strlen(splitted[i - 1]) + 1) != 0)
			return (false);
	}
	if (wildcard[0] != '.' && fname[0] == '.')
		return (false);
	ft_free_split(&splitted);
	return (true);
}
