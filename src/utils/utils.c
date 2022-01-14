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

int	print_error_signaled(int status, char *name)
{
	if (status == 128 + SIGABRT)
		print_error(name, NULL, "abort program", "6");
	else if (status == 128 + SIGBUS)
		print_error(name, NULL, "bus error", "10");
	else if (status == 128 + SIGSEGV)
		print_error(name, NULL, "segmentation violation", "11");
	else if (status == 128 + SIGTERM)
		print_error(name, NULL, "software termination signal", "15");
	return (status);
}

bool	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
