# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 20:05:16 by hbuisser          #+#    #+#              #
#    Updated: 2021/02/23 17:37:19 by hbuisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		philo_one.c \
		utils/utils.c \
		utils/print.c \
		utils/errors_and_free.c \
		utils/libft.c \
		utils/libft2.c
		
OBJS = $(SRCS:%.c=%.o)

NAME = Philosopher

CFLAGS = -g -Wall -Wextra -Werror -pthread

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:		
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all
