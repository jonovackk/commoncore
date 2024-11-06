# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 11:13:08 by jnovack           #+#    #+#              #
#    Updated: 2024/11/06 11:25:18 by jnovack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

TEST_NAME = test_printf

SRC =	ft_printf.c \
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
TEST_OBJS = $(TEST_SRC:.c=.o)
BONUS_OBJS = $(SRC:.c=_bonus.o)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(TEST_NAME): $(NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_NAME) $(TEST_OBJS) -L. -lftprintf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS) $(TEST_OBJS) $(BONUS_OBJS)

clean-win:
	$(RM_WIN) "*.o"

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

fclean-win: clean-win
	$(RM_WIN) "$(NAME)"
	$(RM_WIN) "$(TEST_NAME)"

re: fclean all

.PHONY: all clean clean-win fclean fclean-win re
