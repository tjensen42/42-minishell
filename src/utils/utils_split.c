#include "libft.h"
#include "global.h"

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

int	split_append_str(char ***split, char *str)
{
	int		i;
	char	**new_split;

	new_split = malloc((split_count(*split) + 2) * sizeof(char *));
	if (new_split == NULL)
		return (ERROR);
	i = 0;
	while ((*split)[i])
	{
		new_split[i] = (*split)[i];
		i++;
	}
	new_split[i] = str;
	new_split[i + 1] = NULL;
	free(*split);
	*split = new_split;
	return (0);
}

int	split_remove_str(char ***split, char *remove_str)
{
	int		i;
	char	**new_split;

	if (!split_contains_str(*split, remove_str))
		return (ERROR);
	new_split = malloc(split_count(*split) * sizeof(char *));
	if (new_split == NULL)
		return (ERROR);
	i = 0;
	while ((*split)[i] != remove_str)
	{
		new_split[i] = (*split)[i];
		i++;
	}
	free(remove_str);
	while ((*split)[i + 1])
	{
		new_split[i] = (*split)[i + 1];
		i++;
	}
	new_split[i] = NULL;
	free(*split);
	*split = new_split;
	return (0);
}

int	split_replace_str(char ***split, char *old_str, char *new_str)
{
	int	i;

	if (*split == NULL)
		return (ERROR);
	i = 0;
	while ((*split)[i] && (*split)[i] != old_str)
		i++;
	if ((*split)[i] != old_str)
		return (ERROR);
	free(old_str);
	(*split)[i] = new_str;
	return (0);
}

int	split_contains_str(char **split, char *str)
{
	int	i;

	if (split == NULL || str == NULL)
		return (false);
	i = 0;
	while (split[i] && split[i] != str)
		i++;
	if (split[i] == str)
		return (true);
	return (false);
}
