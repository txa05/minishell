# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: txavier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 10:21:43 by txavier           #+#    #+#              #
#    Updated: 2025/02/27 13:06:42 by txavier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell

SRCS = main.c \
       ./other/utils.c \
       ./other/tokenize.c \
       ./other/redirect.c \
       ./other/redirect_aux.c \
       ./builtins/ft_cd.c \
       ./builtins/ft_pwd.c \
       ./builtins/ft_echo.c \
       ./builtins/ft_export.c \
       ./other/pipes_ft.c \
       ./other/pipes_aux.c \
       ./other/order_input.c \
       ./other/syntaxy_check.c \
       ./other/init.c \
       ./other/tokenize_aux.c \
       ./other/tokenize_aux2.c \
       ./builtins/ft_env.c \
       ./other/expanion_aux.c \
       ./other/my_strtok.c \
       ./other/input_checker.c \
       ./builtins/ft_unset.c \
       ./other/exec_extern_cmd.c \
       ./other/exec_extern_cmd_aux.c \
       ./other/exec_aux.c \
       ./other/create_matrix.c \
       ./other/create_args_matrix.c \
       ./other/exec.c \
       ./other/t_evar_list.c \
       ./other/expanion.c \
       ./other/program_aux.c \
       ./builtins/ft_exit.c \
       ./builtins/ft_exit_aux.c \
       ./builtins/builtins.c

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)
	clear
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	clear
re: fclean all
