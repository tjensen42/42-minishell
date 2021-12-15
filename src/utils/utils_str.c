#include "libft.h"
#include "global.h"

char	*str_append_str(char *str, char *append)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(str, append);
	free(tmp);
	return (str);
}

char	*str_append_chr(char *str, char append)
{
	int		i;
	char	*new_str;

	if (str == NULL)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 2);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = append;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}
