# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 20:05:16 by hbuisser          #+#    #+#              #
#    Updated: 2021/02/22 12:17:49 by hbuisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo_one.c \
		utils/utils.c \
		utils/free.c \
		utils/errors.c \
		utils/libft.c
		
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
