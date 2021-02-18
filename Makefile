# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 20:05:16 by hbuisser          #+#    #+#              #
#    Updated: 2021/02/18 16:04:52 by hbuisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo_one.c \
		utils/utils.c \
		utils/free.c \
		utils/errors.c
		
OBJS = $(SRCS:%.c=%.o)

NAME = Philosopher

CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror -pthread

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:		
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all
