# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/20 16:01:18 by jnovack           #+#    #+#              #
#    Updated: 2025/01/21 17:52:10 by jnovack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SOURCES = sources/conv_functions/ft_atoi.c \
	sources/conv_functions/ft_itoa.c \
	sources/conv_functions/ft_itoa.c \
	sources/desc_file/ft_putchar_fd.c \
	sources/desc_file/ft_putendl_fd.c \
	sources/desc_file/ft_putnbr_fd.c \
	sources/desc_file/ft_putstr_fd.c \
	sources/mnpl_char/ft_isalnum.c \
	sources/mnpl_char/ft_isalpha.c \
	sources/mnpl_char/ft_isascii.c \
	sources/mnpl_char/ft_isdigit.c \
	sources/mnpl_char/ft_isprint.c \
	sources/mnpl_char/ft_putchar.c \
	sources/mnpl_char/ft_putnbr.c \
	sources/mnpl_char/ft_tolower.c \
	sources/mnpl_char/ft_toupper.c \
	sources/mnpl_memory/ft_bzero.c \
	sources/mnpl_memory/ft_calloc.c \
	sources/mnpl_memory/ft_memchr.c \
	sources/mnpl_memory/ft_memcmp.c \
	sources/mnpl_memory/ft_memcpy.c \
	sources/mnpl_memory/ft_memmove.c \
	sources/mnpl_memory/ft_memset.c \
	sources/mnpl_memory/ft_strdup.c \
	sources/mnpl_str/ft_puthex.c \
	sources/mnpl_str/ft_putptr.c \
	sources/mnpl_str/ft_putstr.c \
	sources/mnpl_str/ft_split.c \
	sources/mnpl_str/ft_strchr.c \
	sources/mnpl_str/ft_striteri.c \
	sources/mnpl_str/ft_strjoin.c \
	sources/mnpl_str/ft_strlcat.c \
	sources/mnpl_str/ft_strlcpy.c \
	sources/mnpl_str/ft_strlen.c \
	sources/mnpl_str/ft_strmapi.c \
	sources/mnpl_str/ft_strncmp.c \
	sources/mnpl_str/ft_strnstr.c \
	sources/mnpl_str/ft_strrchr.c \
	sources/mnpl_str/ft_strtrim.c \
	sources/mnpl_str/ft_substr.c \
	sources/get_next_line/get_next_line.c \
	sources/ft_printf/ft_printf.c \
	sources/ft_printf/ft_print_char.c \
	sources/ft_printf/ft_print_hex.c \
	sources/ft_printf/ft_print_char.c \
	sources/ft_printf/ft_print_num_unsigned.c \
	sources/ft_printf/ft_print_ptr.c \
	sources/ft_printf/ft_print_str.c \
	sources/ft_printf/ft_print_num_base.c \
	sources/ft_printf/ft_print_num.c

OBJS = $(SOURCES:.c=.o)



INCS    = ./includes
NAME    = libft.a
LIBC    = ar rc
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -O3 -fPIC
RM      = rm -f

LIGHT_BLUE = \033[38;2;173;216;230m
RESET      = \033[0m

.c.o:
	@echo "$(LIGHT_BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

# Link all object files into the library archive
$(NAME): $(OBJS)
	@echo "$(LIGHT_BLUE)Creating library $(NAME)...$(RESET)"
	$(LIBC) $@ $^

all: $(NAME)

so:
	@echo "$(LIGHT_BLUE)Creating shared library libft.so...$(RESET)"
	$(CC) -nostartfiles ${CFLAGS} ${SOURCES}
	$(CC) -nostartfiles -shared -o libft.so ${OBJS}

clean:
	@echo "$(LIGHT_BLUE)Cleaning up object files...$(RESET)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(LIGHT_BLUE)Removing $(NAME) and libft.so...$(RESET)"
	$(RM) $(NAME)
	$(RM) libft.so

re: fclean all

.PHONY: all so clean fclean re

