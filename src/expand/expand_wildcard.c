#include <dirent.h>
#include "expand.h"

static char **expand_fname_get(void);
static bool expand_token_is_wildcard(t_list *token);
static bool	expand_fname_is_wild(char *fname, t_list *token);
static int	expand_wildcard_token(t_list *token);

int	expand_wildcard(t_c_scmd *c_scmd)
{
	t_list	*iter;

	iter = c_scmd->l_argv;
	while (iter)
	{
		// if (expand_token_is_wildcard(iter))
			if (expand_wildcard_token(iter) == ERROR)
				return (ERROR);
		iter = iter->next;
	}
	iter = c_scmd->l_redir;
	while (iter)
	{
		if (expand_token_is_wildcard(iter))
			if (expand_wildcard_token(iter) == ERROR)
				return (ERROR);
		iter = iter->next;
	}
	return (0);
}

static bool expand_token_is_wildcard(t_list *token)
{
	if (!(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
		&& ft_strchr(token_content(token)->string, '*') == NULL)
		return (true);
	while (token_content(token)->flags & TOK_CONNECTED)
	{
		token = token->next;
		if (!(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
			&& ft_strchr(token_content(token)->string, '*') == NULL)
			return (true);
	}
	return (false);
}

static int	expand_wildcard_token(t_list *token)
{
	int		i;
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
	i = 0;
	while (fname[i])
	{
		if (expand_fname_is_wild(fname[i], token))
		{
			new_token = token_create(fname[i], token_content(token)->flags);
			token_content(token)->flags &= ~(TOK_S_QUOTE | TOK_D_QUOTE);
			if (new_token == NULL)
			{
				print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM);
				ft_lstclear(&l_wildcards, c_token_destroy);
				break ;
			}
			ft_lstadd_back(&l_wildcards, new_token);
		}
		i++;
	}
	while (l_wildcards)
	{
		printf("%s\n", token_content(l_wildcards)->string);
		l_wildcards = l_wildcards->next;
	}

	ft_free_split(&fname);
	return (0);
}

static bool	expand_fname_is_wild(char *fname, t_list *token)
{
	int		i;
	int		j;
	char	*wildcard;
	bool	quoted;

	j = 0;
	while (token)
	{
		quoted = false;
		if (token_content(token)->flags & (TOK_S_QUOTE | TOK_D_QUOTE))
			quoted = true;
		i = 0;
		wildcard = token_content(token)->string;
		while (wildcard && wildcard[i])
		{
			while (!quoted && wildcard[i] == '*' && wildcard[i + 1] == '*')
				i++;
			if (!quoted && wildcard[i] == '*')
				i++;
			// printf("%d\n", i);
			while (wildcard[i] && fname[j] && fname[j] != wildcard[i])
				j++;
			if (fname[j] != wildcard[i])
				return (false);
			while (wildcard[i] && wildcard[i] == fname[j]
					&& (quoted || wildcard[i] != '*'))
			{
				i++;
				j++;
			}
			i++;
		}
		if (token_content(token)->flags & TOK_CONNECTED)
			token = token->next;
		else
			token = NULL;
	}
	return (true);
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









// #include "exec.h"
// #include "cmd.h"

// int	exec_expand_wildcard(t_c_scmd *c_scmd)
// {
// 	t_list	*iter;

// 	iter = c_scmd->l_argv;
// 	while (iter)
// 	{
// 		if (expand_wildcard_needed(iter))
// 		{
// 			if (ft_strnstr())
// 		}
// 		while (token_content(iter)->flags & TOK_CONNECTED)
// 			iter = iter->next;
// 		iter = iter->next;
// 	}
// }


// directory_matches_str(char *dir, char *str)
// {
// 	int	i_dir;
// 	int	i_str;
// 	int	l_dir;
// 	int	l_str;

// 	l_dir = ft_strlen(dir);
// 	l_str = ft_strlen(str);
// 	i_dir = 0;
// 	i_str = 0;
// 	ft_strnstr(&dir[i], &str[i])
// }








// bool	expand_wildcard_needed(t_list *token)
// {
// 	if (token_need_wildcard_expansion(token))
// 		return (true);
// 	while (token_content(token)->flags & TOK_CONNECTED)
// 	{
// 		token = token->next;
// 		if (token_need_wildcard_expansion(token))
// 			return (true);
// 	}
// 	return (false);
// }

// bool	token_need_wildcard_expansion(t_list *token)
// {
// 	if (!(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE)))
// 		if (ft_strchr(token_content(token)->string, '*') == 0)
// 			return (true);
// 	return (false);
// }


// ls *

// ls before*

// ls *after

// ls before*after