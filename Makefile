# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hepple <hepple@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 22:03:08 by tjensen           #+#    #+#              #
#    Updated: 2021/12/10 19:22:03 by hepple           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	Project specific														   #
# **************************************************************************** #

NAME		:= minishell

SRCS		:= minishell.c
SRCS		+= token.c cmd/cmd.c cmd/scmd.c env/env.c

SRCS_LEXER	:= lexer.c lexer_syntax.c lexer_token_other.c lexer_token_text.c
SRCS_PARSER	:= parser.c parser_scmd.c parser_pipeline.c parser_group.c
SRCS_EXEC	:= exec.c exec_pipeline.c exec_pipeline_utils.c exec_scmd.c exec_scmd_utils.c exec_wait.c exec_expand_wildcard.c exec_exit_status.c exec_redir.c
SRCS_BUILTIN:= builtin_echo.c builtin_utils.c builtin_cd.c builtin_exit.c builtin_pwd.c builtin_env.c builtin_export.c builtin_unset.c builtin.c
SRCS_PRINTER:= printer_token.c printer_scmd.c printer_cmd.c
SRCS_SIGNALS:= signals.c
SRCS_UTILS	:= utils.c utils_lst.c utils_split.c

SRCS		+= $(addprefix lexer/, $(SRCS_LEXER)) $(addprefix parser/, $(SRCS_PARSER)) \
			   $(addprefix exec/, $(SRCS_EXEC)) $(addprefix printer/, $(SRCS_PRINTER)) \
			   $(addprefix builtin/, $(SRCS_BUILTIN)) $(addprefix utils/, $(SRCS_UTILS)) \
			   $(addprefix signals/, $(SRCS_SIGNALS))

LDLIBS		:= -lft -lreadline

# **************************************************************************** #
#	GENERAL VARIABLES														   #
# **************************************************************************** #

CC			:= gcc
# CFLAGS		:= -Wall -Wextra -Werror

SDIR		:= src
ODIR		:= obj
OBJS		:= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

LIBDIRS		:= $(wildcard lib/*)
LDLIBS		:= $(addprefix -L./, $(LIBDIRS)) $(LDLIBS)
INCLUDES	:= -I./inc/ $(addprefix -I./, $(LIBDIRS)) \
			   $(addprefix -I./, $(addsuffix /inc, $(LIBDIRS)))

# COLORS
LB   		= \033[0;36m
B			= \033[0;34m
Y  			= \033[0;33m
G		    = \033[0;32m
R 			= \033[0;31m
X		    = \033[m

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# **************************************************************************** #
#	FUNCTIONS									   							   #
# **************************************************************************** #

define MAKE_LIBS
	for DIR in $(LIBDIRS); do \
		$(MAKE) -C $$DIR $(1) --silent; \
	done
endef

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

.PHONY: all $(NAME) header clean fclean re bonus debug release libs test

all: $(NAME)

$(NAME): libs header $(OBJDIRS) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)
	@printf "$(G)======= $(NAME)$(X)\n"

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "%-57b %b" "$(B)compile $(LB)$@" "$(G)[✓]$(X)\n"

header:
	@printf "###############################################\n"
	@printf "$(Y)####### $(shell echo "$(NAME)" | tr '[:lower:]' '[:upper:]')$(X)\n"

clean: libs header
	@$(RM) -r $(ODIR)
	@$(RM) -r *.dSYM $(SDIR)/*.dSYM $(SDIR)/$(NAME)
	@printf "%-50b %b" "$(R)clean" "$(G)[✓]$(X)\n"

fclean: libs header clean
	@$(RM) $(NAME)
	@printf "%-50b %b" "$(R)fclean" "$(G)[✓]$(X)\n"

re: fclean all

bonus: all

debug: CFLAGS += -O0 -DDEBUG -g
debug: all

release: fclean
release: CFLAGS	+= -O2 -DNDEBUG
release: all clean

libs:
ifeq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS), clean fclean re debug release))
	@$(call MAKE_LIBS,$(MAKECMDGOALS))
else
	@$(call MAKE_LIBS,all)
endif

test:
	@cd tests && bash tester.sh
