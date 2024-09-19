# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbbot <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 14:51:08 by fbbot             #+#    #+#              #
#    Updated: 2024/09/19 19:34:51 by fbbot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -lpthread #-g3 -fsanitize=thread 
NAME	= philo
SRCS	= main.c init.c philo_utils.c actions.c check_utils.c
OBJS	= $(SRCS:%.c=%.o)

.PHONY : all re clean fclean

.SECONDARY : $(OBJS)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
