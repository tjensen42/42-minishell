#include "exec.h"
#include "token.h"
#include "env.h"

static int	scmd_find_path(char **path_split, char *scmd);
static char	**path_split_get(void);
static int	path_split_append_slash(char **path_split);

int	scmd_set_path(char **argv)
{
	int		i;
	char	**path_split;

	if (ft_strchr(argv[0], '/') || env_get_value("PATH") == NULL)
	{
		if (access(argv[0], F_OK) == -1)
			return (print_error(SHELL_NAME, argv[0], NULL, strerror(errno)));
	}
	else if (env_get_value("PATH"))
	{
		if ();

	}
	return (0);
}

static int	scmd_set_path(char **argv)
{
	int		i;
	char	**path_split;

	path_split = path_split_get();
	if (path_split == NULL)
		return (ENOMEM);
	i = scmd_find_path(path_split, argv[0]);
}

static int	scmd_find_path(char **path_split, char *scmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_split && path_split[i])
	{
		tmp = ft_strjoin(path_split[i], scmd);
		if (tmp == NULL)
		{
			print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM);
			return (ENOMEM);
		}
		if (access(tmp, F_OK) == 0)
		{
			free(tmp);
			return (i);
		}
		free(tmp);
		i++;
	}
	return (ERROR);
}

static char	**path_split_get(void)
{
	char	**path_split;

	path_split = NULL;
	if (env_get_value("PATH"))
	{
		path_split = ft_split(env_get_value("PATH"), ':');
		if (path_split == NULL)
		{
			print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM);
			return (NULL);
		}
	}
	if (path_split_append_slash(path_split) == ERROR)
	{
		ft_free_split(&path_split);
		return (NULL);
	}
	return (path_split);
}

static int	path_split_append_slash(char **path_split)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_split && path_split[i])
	{
		if (path_split[i][ft_strlen(path_split[i]) - 1] != '/')
		{
			tmp = path_split[i];
			path_split[i] = ft_strjoin(path_split[i], "/");
			if (path_split[i] == NULL)
			{
				path_split[i] = tmp;
				return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
			}
			free(tmp);
		}
		i++;
	}
	return (0);
}

char	**l_token_to_split(t_list *l_token)
{
	int		i;
	char	*tmp;
	char	**split;
	t_list	*iter;

	i = 0;
	iter = l_token;
	while (iter)
	{
		if (!(token_content(iter)->flags & TOK_CONNECTED))
			i++;
		iter = iter->next;
	}
	split = malloc((i + 1) * sizeof(char *));
	i = 0;
	iter = l_token;
	while (iter)
	{
		if (token_content(iter)->flags & TOK_CONNECTED)
		{
			split[i] = ft_strdup(token_content(iter)->string);
			while (token_content(iter)->flags & TOK_CONNECTED)
			{
				tmp = split[i];
				split[i] = ft_strjoin(split[i], token_content(iter->next)->string);
				free(tmp);
				iter = iter->next;
			}
		}
		else
			split[i] = ft_strdup(token_content(iter)->string);
		iter = iter->next;
		i++;
	}
	split[i] = NULL;
	return (split);
}
