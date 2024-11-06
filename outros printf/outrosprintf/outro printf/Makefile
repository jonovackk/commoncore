# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 13:30:12 by jnovack           #+#    #+#              #
#    Updated: 2024/11/04 16:33:31 by jnovack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

# Cores usadas

BLUE =		\033[0;94m
BROWN =		\033[38;2;184;143;29m
MAGENTA =	\033[0;95m
CYAN =		\033[0;96m
GREEN =		\033[0;92m
RED =		\033[0;91m
DEF_COLOR =	\033[0;39m

SRCS = ft_printf.c ft_putchar.c ft_putnbr.c ft_num_nosign.c ft_punt_hexa.c \
		ft_strlen.c ft_putstr.c ft_hexa_min.c ft_hexa_mayus.c

INCLUDE = ft_print.h

CC = gcc
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ${INCLUDE}
	@echo "${BLUE} ◎ $(BROWN)Compiling  ${MAGENTA}→  $(CYAN)< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -c $< -o $@

OBJS = ${SRCS:.c=.o}

all:	${NAME}

${NAME}: ${OBJS}
		@${AR} ${NAME} ${OBJS}
		@echo "\n$(GREEN) Created $(NAME) ✓ $(DEF_COLOR)\n"

clean:
		@${RM} ${OBJS}
		@echo "\n${BLUE} ◎ $(RED)All objects cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"

fclean:
		@${RM} ${OBJS}
		@${RM} ${NAME}
		@echo "\n${BLUE} ◎ $(RED)All objects and executable cleaned successfully${BLUE} ◎$()DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
