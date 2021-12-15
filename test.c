#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int	main(void)
{
	char c;
	char buf[200];

	c = -1;
	if (write(0, "Hello 42\nHello Code\n", 21) < 0)
		perror("");
	if (write(0, &c, 1) < 0)
		perror("");
	int size = read(0, buf, 1);
	buf[size] = '\0';
	write(1, buf, size);
	write(1, "\n", 1);
}




static bool	expand_wildcard_match_fname(char *wildcard, char *fname)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (wildcard[i])
	{
		if (wildcard[i] == WILDCARD)
		{
			i++;
			while (fname[j] && fname[j] != wildcard[i])
				j++;
		}
		else
		{
			if (wildcard[i] != fname[j])
				return (false);
			i++;
			j++;
		}
	}
	if (fname[j] == '\0')
		return (true);
	return (false);
}

