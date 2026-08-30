# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#              #
#    Updated: 2026/08/19 13:44:21 by kchibukh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = cleanup.c coder.c dongle.c heap.c init.c logging.c main.c monitor.c parsing.c schedualer.c simulation.c time.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
    ar -rcs $(NAME) $^

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re: fclean all	

.PHONY: all clean fclean re
