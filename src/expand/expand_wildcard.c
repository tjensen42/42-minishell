#include "expand.h"

static t_list	*expand_wildcard_token(t_list *token);
static bool	expand_wildcard_match_fname(char *wildcard, char **split, char *fname);
static int	expand_wildcard_list(t_list	*l_token);
static t_list	*expand_wildcard_to_list(char *wildcard, char **split, char **fname, int flags);

int	expand_wildcard(t_c_scmd *c_scmd)
{
	int	status;

	status = 0;
	status = expand_wildcard_list(c_scmd->l_argv);
	status = expand_wildcard_list(c_scmd->l_redir);
	return (status);
}

static int	expand_wildcard_list(t_list	*l_token)
{
	t_list	*new_token;

	while (l_token)
	{
		if (expand_token_is_wildcard(l_token))
		{
			new_token = expand_wildcard_token(l_token);
			if (new_token == NULL)
				return (ERROR);
		}
		else
		{
			while (token_content(l_token)->flags & TOK_CONNECTED)
				l_token = l_token->next;
		}
		l_token = l_token->next;
	}
	return (0);
}

static t_list	*expand_wildcard_token(t_list *token)
{
	char	*wildcard;
	char	**fname;
	char	**split;
	t_list	*l_wildcards;

	wildcard = expand_wildcard_get(token);
	fname = expand_fname_get();
	split = ft_split(wildcard, WILDCARD);
	if (wildcard == NULL || fname == NULL || split == NULL)
	{
		free(wildcard);
		if (fname != NULL)
			ft_free_split(&fname);
		if (split != NULL)
			ft_free_split(&split);
		print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM);
		return (NULL);
	}
	l_wildcards = expand_wildcard_to_list(wildcard, split, fname,
										token_content(token)->flags);
	while (l_wildcards)
	{
		printf("%s\n", token_content(l_wildcards)->string);
		l_wildcards = l_wildcards->next;
	}
	free(wildcard);
	ft_free_split(&fname);
	ft_free_split(&split);
	return (l_wildcards);
}

static t_list	*expand_wildcard_to_list(char *wildcard, char **split, char **fname, int flags)
{
	int		i;
	char	*tmp;
	t_list	*new_token;
	t_list	*l_wildcards;

	l_wildcards = NULL;
	i = 0;
	while (fname[i])
	{
		if (expand_wildcard_match_fname(wildcard, split, fname[i]))
		{
			tmp = ft_strdup(fname[i]);
			new_token = token_create(tmp, flags);
			if (tmp == NULL || new_token == NULL)
			{
				ft_lstdelone(new_token, c_token_destroy);
				ft_lstclear(&l_wildcards, c_token_destroy);
				return (NULL);
			}
			token_content(new_token)->flags &= ~(TOK_CONNECTED | TOK_D_QUOTE | TOK_S_QUOTE);
			ft_lstadd_back(&l_wildcards, new_token);
		}
		i++;
	}
	return (l_wildcards);
}

static bool	expand_wildcard_match_fname(char *wildcard, char **split, char *fname)
{
	int		i;
	char	*shift_fname;

	shift_fname = fname;
	i = 0;
	while (split[i])
	{
		shift_fname = ft_strnstr(shift_fname, split[i], ft_strlen(shift_fname));
		if (shift_fname == NULL)
			return (false);
		shift_fname += ft_strlen(split[i]);
		i++;
	}
	if (wildcard[0] != WILDCARD
		&& ft_strncmp(fname, split[0], ft_strlen(split[0])) != 0)
		return (false);
	if (wildcard[ft_strlen(wildcard) - 1] != WILDCARD
		&& ft_strncmp(fname + ft_strlen(fname) - ft_strlen(split[i - 1]),
			split[i - 1], ft_strlen(split[i - 1]) + 1) != 0)
			return (false);
	if (wildcard[0] != '.' && fname[0] == '.')
		return (false);
	return (true);
}
