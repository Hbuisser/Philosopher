# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 20:05:16 by hbuisser          #+#    #+#              #
#    Updated: 2021/03/02 14:47:59 by hbuisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		philo_two.c \
		utils/errors_init_and_free.c \
		utils/parse.c \
		utils/print.c \
		utils/utils.c \
		utils/libft.c \
		utils/libft2.c
		
OBJS = $(SRCS:%.c=%.o)

NAME = philo_two

CFLAGS = -g -Wall -Wextra -Werror -pthread 

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:		
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all
