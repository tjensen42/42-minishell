#include "exec.h"
#include "token.h"

void	environ_path_append_slash(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/");
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}

char	**environ_path_get(void)
{
	int			i;
	char		**paths;
	extern char	**environ;

	if (environ == NULL)
		return (NULL);
	paths = NULL;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			paths = ft_split((environ[i] + 5), ':');
			if (paths == NULL)
				return (NULL);
			environ_path_append_slash(paths);
			break ;
		}
		i++;
	}
	return (paths);
}

int	pipex_cmd_set_path(char **cmd)
{
	int		i;
	char	*cmd_tmp;
	char	**paths;

	if (access(*cmd, F_OK) == 0)
		return (0);
	paths = environ_path_get();
	if (paths == NULL)
		return (ERROR);
	i = 0;
	while (paths[i])
	{
		cmd_tmp = ft_strjoin(paths[i], *cmd);
		if (access(cmd_tmp, F_OK) == 0)
		{
			free(*cmd);
			*cmd = cmd_tmp;
			ft_free_split(&paths);
			return (0);
		}
		free(cmd_tmp);
		i++;
	}
	ft_free_split(&paths);
	return (127);
}

char	**list_to_split(t_list *l_token)
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

