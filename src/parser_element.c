#include "parser.h"

t_c_element	*parser_c_element_get(t_list *l_token)
{
	int 		type;
	int 		status;
	t_c_element	*c_element;

	c_element = malloc(sizeof(t_c_element));
	if (c_element == NULL)
		return (NULL);
	type = parser_get_type(l_token);
	if (type == PAR_CMD)
	{
		status = parser_cmd_set(c_element, l_token);
		if (status == ERROR)
		{
			parser_c_element_destroy(&c_element);
			return (NULL);
		}
	}
	else
	{
		c_element->type = type;
		c_element->cmd = NULL;
		c_element->redirs = NULL;
		c_element->files = NULL;
	}
	return (c_element);
}

void	parser_c_element_destroy(void *c_element)
{
	if (c_element)
	{
		ft_free_split(&(((t_c_element *)c_element)->cmd));
		ft_free_split(&(((t_c_element *)c_element)->redirs));
		ft_free_split(&(((t_c_element *)c_element)->files));
		free(c_element);
	}
}

t_c_element *element_content(t_list *element)
{
	return ((t_c_element *)element->content);
}
