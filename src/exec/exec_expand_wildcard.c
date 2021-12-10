// #include <dirent.h>

// #include "exec.h"
// #include "cmd.h"

// int	exec_expand_wildcard(t_c_scmd *c_scmd)
// {
// 	t_list	*iter;

// 	iter = c_scmd->l_argv;
// 	while (iter)
// 	{
// 		if (expand_wildcard_needed(iter))
// 		{
// 			if (ft_strnstr())
// 		}
// 		while (token_content(iter)->flags & TOK_CONNECTED)
// 			iter = iter->next;
// 		iter = iter->next;
// 	}
// }

// int	expand_wildcard_token(t_c_scmd *c_scmd)
// {
// 	DIR				*dir;
// 	struct dirent	*dirent;

// 	dir = opendir("./");
// 	if (dir == NULL)
// 		return (print_error(SHELL_NAME, NULL, NULL, strerror(errno)));
// 	dirent = readdir(dir);
// 	while (dirent)
// 	{
// 		if ()
// 		dirent = readdir(dir);
// 	}
// 	closedir(dir);
// 	return (0);
// }

// directory_matches_str(char *dir, char *str)
// {
// 	int	i_dir;
// 	int	i_str;
// 	int	l_dir;
// 	int	l_str;

// 	l_dir = ft_strlen(dir);
// 	l_str = ft_strlen(str);
// 	i_dir = 0;
// 	i_str = 0;
// 	ft_strnstr(&dir[i], &str[i])
// }








// bool	expand_wildcard_needed(t_list *token)
// {
// 	if (token_need_wildcard_expansion(token))
// 		return (true);
// 	while (token_content(token)->flags & TOK_CONNECTED)
// 	{
// 		token = token->next;
// 		if (token_need_wildcard_expansion(token))
// 			return (true);
// 	}
// 	return (false);
// }

// bool	token_need_wildcard_expansion(t_list *token)
// {
// 	if (!(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE)))
// 		if (ft_strchr(token_content(token)->string, '*') == 0)
// 			return (true);
// 	return (false);
// }


// ls *

// ls before*

// ls *after

// ls before*after
