#include "libft.h"
#include "global.h"

int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (ERROR);
}

int	print_error_errno(char *s1, char *s2, char *s3)
{
	print_error(s1, s2, s3, strerror(errno));
	errno = 0;
	return (ERROR);
}

bool	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*append_char(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	new_str = malloc(sizeof(char) * (i + 2));
	if (new_str == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

int	get_next_line(char **line, int fd)
{
	int		check;
	char	buffer;

	if (line == NULL)
		return (-1);
	*line = malloc(sizeof(char) * 1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	while ((check = read(fd, &buffer, 1)) > 0)
	{
		if (buffer == '\n')
			break ;
		*line = append_char(*line, buffer);
		if (*line == NULL)
			return (-1);
	}
	return (check);
}
