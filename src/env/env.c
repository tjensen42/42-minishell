#include "libft.h"
#include "env.h"
#include "global.h"
#include "lexer.h"

int	env_init(void)
{
	int			i;
	extern char	**environ;

	i = split_count(environ);
	if (i == 0)
		return (0);
	g_env = malloc((i + 1) * sizeof(char *));
	if (g_env == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	i = 0;
	while (environ[i])
	{
		g_env[i] = ft_strdup(environ[i]);
		if (g_env[i] == NULL)
		{
			ft_free_split(&g_env);
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
		}
		i++;
	}
	g_env[i] = NULL;
	return (0);
}

/* Searchs for a env variable "name" and returns a pointer to it's value */
char	*env_get_value(char *name)
{
	char	*env_var;

	env_var = env_find_var(name);
	if (env_var)
		return (ft_strchr(env_var, '=') + 1);
	else
		return (NULL);
}

/* Searchs for a env variable "name" and returns a pointer to the whole variable including the name */
char	*env_find_var(char *name)
{
	int	i;
	int	l_name;

	if (name == NULL || g_env == NULL)
		return (NULL);
	if (ft_strchr(name, '='))
		l_name = ft_strchr(name, '=') - name;
	else
		l_name = ft_strlen(name);
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(name, g_env[i], l_name) && g_env[i][l_name] == '=')
			return (g_env[i]);
		i++;
	}
	return (NULL);
}

int	env_unset_var(char *name)
{
	char	*env_var;

	env_var = env_find_var(name);
	if (env_var == NULL)
		return (ERROR);
	split_remove_str(&g_env, env_var);
	return (0);
}

int	env_put_var(char *str)
{
	int		i;
	int		status;
	char	*new_var;
	char	*old_var;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return (ERROR);
	new_var = ft_strdup(str);
	if (new_var == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	old_var = env_find_var(str);
	status = split_replace_str(&g_env, old_var, new_var);
	if (status == ERROR)
	{
		status = split_append_str(&g_env, new_var);
		if (status == ERROR)
			return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	}
	return (0);
}

int		env_set_env(char *name, char *value)
{
	char	*tmp;
	char	*var_str;

	if (name == NULL || value == NULL)
		return (ERROR);
	tmp = ft_strjoin(name, "=");
	if (tmp == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	var_str = ft_strjoin(tmp, value);
	free(tmp);
	if (var_str == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	return (env_put_var(var_str));
}

bool	env_var_is_value(char *var_name, char *value)
{
	char	*env_value;

	env_value = env_get_value(var_name);
	if (env_value)
		if (ft_strncmp(env_value, value, ft_strlen(value) + 1) == 0)
			return (true);
	return (false);
}
