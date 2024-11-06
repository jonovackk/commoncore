# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 19:56:53 by vigde-ol          #+#    #+#              #
#    Updated: 2024/10/30 19:56:59 by vigde-ol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome da biblioteca
NAME = libftprintf.a

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar crs

# Comandos de remoção para multiplataforma
RM = rm -rf
RM_WIN = del /S /Q

# Fontes e objetos
SRC = ft_printf.c ft_print_char.c ft_print_string.c ft_print_pointer.c \
      ft_print_int.c ft_print_unsigned.c ft_print_hex_lower.c \
      ft_print_hex_upper.c ft_print_percent.c ft_putnbr_fd.c
OBJS = $(SRC:.c=.o)

# Regra principal: compila e cria a biblioteca
$(NAME): $(OBJS)
	$(AR) $@ $^

# Regra para compilar cada arquivo .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Alvo principal
all: $(NAME)

# Limpeza dos objetos no Linux
clean:
	$(RM) $(OBJS)

# Limpeza completa no Linux
fclean: clean
	$(RM) $(NAME)

# Limpeza dos objetos e da biblioteca no Windows
clean-win:
	$(RM_WIN) "*.o"

fclean-win: clean-win
	$(RM_WIN) "$(NAME)"

# Recompila tudo
re: fclean all

# Especifica alvos para o Make ignorar arquivos com os mesmos nomes
.PHONY: all clean fclean clean-win fclean-win re
