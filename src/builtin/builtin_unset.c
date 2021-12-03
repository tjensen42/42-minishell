#include "builtin.h"

int	builtin_unset(int argc UNUSED, char **argv)
{
	if (argv[1] == NULL)
		return (ERROR);
	if (ft_strchr(argv[1], '=') )
	return (env_unset_var(argv[1]));
}
