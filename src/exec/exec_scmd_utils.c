#include "exec.h"
#include "token.h"
#include "env.h"
#include <sys/stat.h>

static char	**path_split_get(void);
static int	path_split_append_slash(char **path_split);
static int	path_split_set(char **path_split, char **argv);

int	scmd_search_path(char **argv)
{
	char	**path_split;

	path_split = NULL;
	if (env_get_value("PATH") && argv[0][0] != '\0')
	{
		path_split = path_split_get();
		if (path_split == NULL)
			return (ERROR);
		if (path_split_set(path_split, argv) == 0)
		{
			ft_free_split(&path_split);
			return (0);
		}
	}
	if (path_split)
		ft_free_split(&path_split);
	return (ERROR);
}

/* Returns 0 if a path was found, if no path matches it returns ERROR and the argv[0] leaves untouched  */
static int	path_split_set(char **path_split, char **argv)
{
	int			i;
	char		*tmp;
	struct stat	s;

	i = 0;
	while (path_split && path_split[i])
	{
		tmp = ft_strjoin(path_split[i], *argv);
		if (tmp == NULL)
		{
			print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM);
			return (ERROR);
		}
		if (access(tmp, F_OK) == 0 && (!stat(tmp, &s) && !S_ISDIR(s.st_mode)))
		{
			free(*argv);
			*argv = tmp;
			return (0);
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
