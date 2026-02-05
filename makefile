# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 14:51:25 by nbaldes           #+#    #+#              #
#    Updated: 2026/02/02 16:00:42 by nbaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

SRC =	philo.c \
		utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re