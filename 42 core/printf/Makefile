# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 11:41:33 by jnovack           #+#    #+#              #
#    Updated: 2024/11/05 11:49:57 by jnovack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	ft_printf.c\
		ft_print_char.c \
		ft_print_str.c \
		ft_print_num.c \
		ft_print_num_base.c \
		ft_print_num_unsigned.c \
		ft_print_ptr.c \
		ft_print_hex.c

TEST_SRC = test.c
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I .
RM = rm -rf
RM_WIN = del /S /Q
AR = ar crs

OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

clean-win:
	$(RM_WIN) "*.o"

fclean: clean
	$(RM) $(NAME)

fclean-win:	clean-win
	$(RM_WIN) "$(NAME)"

re:	fclean all

.PHONY: all clean clean-win fclean fclean-win re


		
