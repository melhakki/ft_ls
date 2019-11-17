# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/08 16:07:01 by sel-mort          #+#    #+#              #
#    Updated: 2019/09/23 18:50:52 by melhakki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = srcs/args.c srcs/args2.c srcs/files.c srcs/free.c srcs/main.c srcs/permissions.c srcs/permissions2.c srcs/permissions3.c srcs/print.c srcs/print2.c srcs/suppliment.c srcs/read.c srcs/sort.c srcs/sort2.c srcs/colors.c

OBJ = $(SRCS:.c=.o)

LIBFT = libft/libft.a

FLAGS = -Wall -Werror -Wextra

CMD = gcc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)

$(NAME): $(OBJ)
		make -C libft/
		$(CMD)

$(OBJ): %.o : %.c
	gcc -o $@ -c $< $(FLAGS)
clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean:clean
	make -C libft/ fclean
	rm -rf $(NAME)

re:fclean all
	make -C libft/ re
