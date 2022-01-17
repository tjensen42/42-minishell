/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepple <hepple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:45:46 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 15:45:59 by hepple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redir.h"

static int	scmd_token_set(t_c_scmd *c_scmd, t_list **l_token);

t_list	*parser_scmd_tokens(t_list *l_token)
{
	t_list	*l_scmd;
	t_list	*scmd;
	t_list	*next;

	l_scmd = NULL;
	while (l_token != NULL)
	{
		scmd = scmd_create(cmd_type_from_token(l_token));
		if (scmd == NULL
			|| (scmd_content(scmd)->type == CMD_SCMD
				&& scmd_token_set(scmd_content(scmd), &l_token) == ERROR))
		{
			ft_lstclear(&l_scmd, c_scmd_destroy);
			return (NULL);
		}
		if (scmd_content(scmd)->type != CMD_SCMD)
		{
			next = l_token->next;
			ft_lstdelone(l_token, c_token_destroy);
			l_token = next;
		}
		ft_lstadd_back(&l_scmd, scmd);
	}
	return (l_scmd);
}

static int	scmd_token_set(t_c_scmd *c_scmd, t_list **l_token)
{
	t_list	*next;

	while (cmd_type_from_token(*l_token) == CMD_SCMD)
	{
		next = (*l_token)->next;
		if (token_content(*l_token)->flags & TOK_REDIR)
		{
			if (redir_type(token_content(*l_token)->str) == REDIR_HEREDOC)
			{
				if (parser_heredoc(*l_token) == ERROR)
					return (ERROR);
			}
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		}
		else if (token_content(*l_token)->flags & TOK_REDIR_FILE)
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		else
			ft_lstadd_back(&(c_scmd->l_argv), *l_token);
		(*l_token)->next = NULL;
		*l_token = next;
	}
	return (0);
}
