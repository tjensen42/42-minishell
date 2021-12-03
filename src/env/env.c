#include "libft.h"
#include "env.h"
#include "global.h"
#include "lexer.h"

// static bool env_i_is_name(char *env_i, char *name);

int	env_init(void)
{
	int			i;
	extern char	**environ;

	i = count_str_array(environ);
	if (i == 0)
		return (0);
	g_env = malloc((i + 1) * sizeof(char *));
	if (g_env == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, ERR_NO_MEM));
	i = 0;
	while (environ && environ[i])
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

// char	*env_get_value(char *name)
// {
// 	int	i;
// 	int	l_name;

// 	if (name == NULL)
// 		return (NULL);
// 	l_name = ft_strlen(name);
// 	i = 0;
// 	while (g_env && g_env[i])
// 	{
// 		if (env_i_is_name(g_env[i], name))
// 			return (g_env[i] + l_name + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

// int	env_unset_var(char *name)
// {
// 	int		i;
// 	int		j;
// 	char	**new_env;

// 	if (env_get_value(name))
// 	{
// 		new_env = malloc(count_str_array(g_env) * sizeof(char *));
// 		if (new_env == NULL)
// 			return (print_error(SHELL_NAME, ERR_NO_MEM, NULL, NULL));
// 		i = 0;
// 		j = 0;
// 		while (g_env[j])
// 		{
// 			if (env_i_is_name(g_env[j], name))
// 				free(g_env[j]);
// 			else
// 				new_env[i++] = g_env[j];
// 			j++;
// 		}
// 		new_env[i] = NULL;
// 		free(g_env);
// 		g_env = new_env;
// 	}
// 	return (0);
// }

// int	env_put_var(char *str)
// {
// 	int		i;
// 	char	*tmp;

// 	if (str == NULL)
// 		return (ERROR);
// 	else if (ft_strchr(str, '=') == NULL)
// 		return (0);
// 	tmp = ft_strdup(str);
// 	if (tmp == NULL)
// 		return (print_error(SHELL_NAME, ERR_NO_MEM, NULL, NULL));
// 	if () // env is inside
// 	{
// 		i = ;
// 		split_replace_str_i(&g_env, i, tmp);
// 	}
// 	else
// 		split_append_str(&g_env, tmp);
// 	return (0);
// }

// static bool env_i_is_name(char *env_i, char *name)
// {
// 	int	l_name;

// 	l_name = ft_strlen(name);
// 	if (!ft_strncmp(name, env_i, l_name) && env_i[l_name] == '=')
// 		return (true);
// 	return (false);
// }

// bool	env_is_valid_name(char *name)
// {
// 	int	i;

// 	if (name[0] == '\0')
// 		return (false);
// 	i = 0;
// 	while (name[i])
// 	{
// 		if (ft_strchr(WHITESPACES, name[i]))
// 			return (false);
// 		else if (ft_strchr(QUOT_MARKS, name[i]))
// 			return (false);
// 	}
// 	return (true);
// }
