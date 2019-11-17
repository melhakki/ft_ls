# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/09 11:08:32 by sel-mort          #+#    #+#              #
#    Updated: 2019/09/24 15:58:33 by melhakki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_putchar.c ft_putendl.c ft_putnbr.c ft_putstr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strsub.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRCS)
	ar cr $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
