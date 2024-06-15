# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 13:21:33 by yalechin          #+#    #+#              #
#    Updated: 2024/06/09 10:23:35 by yalechin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBFT = libft


CFILES = minishell.c

OFILES = $(CFILES:.c=.o)

CC = cc
HEAD =  -I$(LIBFT)
CFLAGS = -Wall -Werror -Wextra -g 
LFLAGS = -L$(LIBFT) -lft -lreadline

all: lib $(NAME) 

lib:
	@make -C $(LIBFT)


$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(HEAD) $^ -L$(LIBFT) $(LFLAGS) -o $(NAME) 

%.o: %.c libft/libft.h minishell.h
	cc $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OFILES)
	@make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean flcean all re lib