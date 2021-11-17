#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"
# include "global.h"
# include "token.h"
# include "cmd.h"

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

t_list		*parser(t_list *l_token);

int			parser_list_group(t_list **l_pipeline);
t_list		*parser_list_group_merge(t_list *open);

int			parser_list_pipeline_pg(t_list **l_cmd);
t_list		*parser_list_pipeline_merge(t_list *start);

t_list		*parser_list_pipeline(t_list *l_scmd);

t_c_cmd		*parser_c_pipeline_get(t_list **l_scmd);
int			parser_pipeline_set(t_c_cmd *c_pipeline, t_list **l_scmd);

int			parser_get_list_type(t_list *lst);

#endif
