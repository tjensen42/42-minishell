#include "exec.h"
#include "token.h"
#include "env.h"

static char	*path_try_path_split(char **path_split, char *cmd);
static char	**path_split_get(void);

int	scmd_set_path(char **argv)
{
	char	*tmp;
	char	*path;
	char	**path_split;

	path_split = NULL;
	if ((ft_strchr(argv[0], '/') || env_find_var("PATH") == NULL)
		&& access(argv[0], F_OK) == -1)
		return (print_error(SHELL_NAME, argv[0], NULL, strerror(errno)));
	else if (!ft_strchr(argv[0], '/') && env_find_var("PATH"))
	{
		path_split = ft_split(env_get_value("PATH"), ':');
		if (path_split == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		path = path_try_path_split(path_split, argv[0]);
		if (path == NULL)
			ft_free_split(&path_split);
		if (path == NULL)
			return (print_error(SHELL_NAME, argv[0], NULL, "command not found"));
		tmp = argv[0];
		argv[0] = ft_strjoin(path, argv[0]);
		if (argv[0] == NULL)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		free(tmp);
	}
	ft_free_split(&path_split);
	return (0);
}

// static char	*path_set_path_split(char **argv)
// {

// }

static char	*path_try_path_split(char **path_split, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

static char	**path_split_get(void)
{
	int		i;
	char	*tmp;
	char	**path_split;

	path_split = ft_split(env_get_value("PATH"), ':');
	if (path_split == NULL)
		return (NULL);
	i = 0;
	while (path_split[i])
	{
		if (path_split[i][ft_strlen(path_split[i]) - 1] != '/')
		{
			tmp = path_split[i];
			path_split[i] = ft_strjoin(path_split[i], "/");
			free(tmp);
		}
		i++;
	}
	return (path_split);
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

