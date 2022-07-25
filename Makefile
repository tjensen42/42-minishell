# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2022/07/25 20:43:58 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -O2

CPPFLAGS    := -I./inc -I./lib/libft/inc
DEPFLAGS     = -MT $@ -MMD -MP -MF $(DDIR)/$*.d

LDFLAGS     := -L./lib/libft
LDLIBS      := -lft -lreadline

VPATH       := src/ src/builtin/ src/cmd/ src/env/ src/exec/ src/expand/ \
			   src/lexer/ src/parser/ src/printer/ src/redir/ src/signals/ \
			   src/token/ src/utils/
SRCS        := minishell.c
SRCS        += builtin_echo.c builtin_cd.c builtin_exit.c builtin_pwd.c \
			   builtin_env.c builtin_export.c builtin_unset.c builtin.c
SRCS        += cmd.c scmd.c
SRCS        += env.c env_modify.c
SRCS        += exec.c exec_pipeline.c exec_pipeline_pipes.c exec_scmd.c \
			   exec_scmd_path.c exec_wait.c exec_group.c exec_exit_status.c
SRCS        += expand.c expand_wildcard.c expand_wildcard_utils.c \
			   expand_var.c expand_var_split.c
SRCS        += lexer.c lexer_syntax.c lexer_token_other.c lexer_token_text.c
SRCS        += parser.c parser_scmd.c parser_pipeline.c parser_group.c \
			   parser_heredoc.c
SRCS        += printer_token.c printer_scmd.c printer_cmd.c
SRCS        += redir.c redir_undo.c
SRCS        += signals.c
SRCS        += token.c token_list.c
SRCS        += utils_error.c utils_gnl.c utils_lst.c utils_split.c utils_str.c

ODIR        := obj
OBJS        := $(SRCS:%.c=$(ODIR)/%.o)

DDIR        := $(ODIR)/.deps
DEPS        := $(SRCS:%.c=$(DDIR)/%.d)

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# **************************************************************************** #
#   RULES                                                                      #
# **************************************************************************** #

.PHONY: all clean fclean re test

$(NAME): lib/libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(ODIR)/%.o: %.c $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

$(DDIR):
	mkdir -p $@

%.a:
	$(MAKE) -C $(dir $@)

all: $(NAME)

clean:
	$(MAKE) -C lib/libft fclean
	$(RM) -r $(DDIR) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	@cd tests && bash tester.sh a

$(DEPS):
include $(wildcard $(DEPS))
