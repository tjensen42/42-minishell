/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:41:01 by hepple            #+#    #+#             */
/*   Updated: 2022/01/17 16:09:47 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	syntax_bin_op(t_list *l_token);
static int	syntax_pipe(t_list *l_token);
static int	syntax_brackets(t_list *l_token);
static int	syntax_missing_op(t_list *l_token);

int	lexer_syntax_check(t_list *l_token)
{
	if (syntax_brackets(l_token) == ERROR)
		return (ERROR);
	if (syntax_bin_op(l_token) == ERROR)
		return (ERROR);
	if (syntax_pipe(l_token) == ERROR)
		return (ERROR);
	if (syntax_missing_op(l_token) == ERROR)
		return (ERROR);
	return (0);
}

static int	syntax_bin_op(t_list *l_token)
{
	if (l_token && token_content(l_token)->flags & TOK_BIN_OP)
		return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_LIST));
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_BIN_OP)
		{
			if (l_token->next == NULL)
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_LIST));
			else if (token_content(l_token->next)->flags
				& (TOK_BIN_OP | TOK_PIPE))
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_LIST));
			else if (token_content(l_token->next)->flags & TOK_C_BRACKET)
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_LIST));
		}
		if (token_content(l_token)->flags & TOK_O_BRACKET)
		{
			if (l_token->next
				&& token_content(l_token->next)->flags & TOK_BIN_OP)
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_LIST));
		}
		l_token = l_token->next;
	}
	return (0);
}

static int	syntax_pipe(t_list *l_token)
{
	if (l_token && token_content(l_token)->flags & TOK_PIPE)
		return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_PIPE)
		{
			if (l_token->next == NULL)
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
			else if (token_content(l_token->next)->flags
				& (TOK_BIN_OP | TOK_PIPE))
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
			else if (token_content(l_token->next)->flags & TOK_C_BRACKET)
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
		}
		if (token_content(l_token)->flags & TOK_O_BRACKET)
		{
			if (l_token->next && token_content(l_token->next)->flags & TOK_PIPE)
				return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_PIPE));
		}
		l_token = l_token->next;
	}
	return (0);
}

static int	syntax_brackets(t_list *l_token)
{
	int	count;

	count = 0;
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_O_BRACKET)
		{
			count++;
			if (l_token->next
				&& token_content(l_token->next)->flags & TOK_C_BRACKET)
			{
				print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_EMPTY_BRACKET);
				return (ERROR);
			}
		}
		else if (token_content(l_token)->flags & TOK_C_BRACKET)
			count--;
		if (count < 0)
			return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_UNO_BRACKET));
		l_token = l_token->next;
	}
	if (count > 0)
		return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_UNC_BRACKET));
	return (0);
}

static int	syntax_missing_op(t_list *l_token)
{
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_C_BRACKET
			&& l_token->next
			&& token_content(l_token->next)->flags & TOK_O_BRACKET)
			return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_MISS_OP));
		else if (token_content(l_token)->flags & TOK_C_BRACKET
			&& token_is_cmd(l_token->next))
			return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_MISS_OP));
		else if (token_is_cmd(l_token)
			&& l_token->next
			&& token_content(l_token->next)->flags & TOK_O_BRACKET)
			return (print_error(SHELL_NAME, ERR_SYNTAX, NULL, ERR_MISS_OP));
		l_token = l_token->next;
	}
	return (0);
}
