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

// PARSER
t_list		*parser(t_list *l_token);

// PARSER_SCMD
t_list		*parser_scmd_tokens(t_list *l_token);
t_list		*parser_scmd_pipelines(t_list *l_scmd);

// PARSER_CMD_PIPELINE
int			parser_cmd_pipeline_merge(t_list **l_cmd);

// PARSER_CMD_GROUP
int			parser_cmd_group_merge(t_list **l_cmd);

// PARSER_HEREDOC
int			parser_heredoc(t_list *l_token);

#endif
