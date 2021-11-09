#include "minishell.h"
#include "parser.h"

t_list	*expander(t_list *l_parse)
{
	while (l_parse != NULL)
	{
		if (scmd_content(l_parse)->type == PAR_SCMD)
		{

		}
		l_parse = l_parse->next;
	}
}

bool	expander_check_variables(char **split)
{
	int		i;
	int		j;
	bool	double_quotes;

	double_quotes = false;
	i = 0;
	while (split && split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '\"')
				double_quotes = !double_quotes;
			else if (!double_quotes && split[i][j] == '\'')
			{
				j++;
				while (split && split[i][j] != '\'')
					j++;
			}
			else if (split[i] == '$')
			{
				if (expander_check_variable_syntax(&split[i][j]) == true)
				{
					ft_substr
				}
			}
			j++;
		}
		i++;
	}
}

bool	expander_check_variable_syntax(char *dollar)
{
	if ((dollar + 1) == '$')
		return (false);
	else if (ft_strchr(WHITESPACES, dollar + 1))
		return (false);
	else if (ft_strchr(QUOT_MARKS, dollar + 1))
		return (false);
	else
		return (true);
}
