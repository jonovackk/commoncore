# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/20 16:01:18 by jnovack           #+#    #+#              #
#    Updated: 2024/10/29 10:18:21 by jnovack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


STR_SRCS = ft_strlen.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strncmp.c \
	   ft_strnstr.c \
	   ft_strdup.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_strmapi.c \
	   ft_striteri.c
	   
MEM_SRCS = ft_bzero.c \
           ft_memcpy.c \
           ft_memset.c \
           ft_memmove.c \
           ft_memchr.c \
           ft_memcmp.c \
           ft_calloc.c
           
CHAR_SRCS = ft_isalnum.c \
            ft_isalpha.c \
            ft_isascii.c \
            ft_isdigit.c \
            ft_isprint.c \
            ft_toupper.c \
            ft_tolower.c
            
UTIL_SRCS = ft_atoi.c \
	    ft_itoa.c
	    
FD_SRCS = ft_putchar_fd.c \
          ft_putstr_fd.c \
          ft_putendl_fd.c \
          ft_putnbr_fd.c
          
SRCS = $(STR_SRCS) $(MEM_SRCS) $(CHAR_SRCS) $(UTIL_SRCS) $(FD_SRCS)
OBJS = $(SRCS:.c=.o)


BONUS_SRCS = ft_lstnew_bonus.c \
             ft_lstadd_front_bonus.c \
             ft_lstsize_bonus.c \
             ft_lstlast_bonus.c \
             ft_lstadd_back_bonus.c \
             ft_lstdelone_bonus.c \
             ft_lstclear_bonus.c \
             ft_lstiter_bonus.c \
             ft_lstmap_bonus.c
           
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

INCS    = ./
NAME    = libft.a
LIBC    = ar rc
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -O3
RM      = rm -f

LIGHT_BLUE = \033[38;2;173;216;230m
RESET	   = \033[0m

.c.o:
	@echo "$(LIGHT_BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

# Link all object files into the library archive
$(NAME): $(OBJS)
	@echo "$(LIGHT_BLUE)Creating library $(NAME)...$(RESET)"
	$(LIBC) $@ $^

all: $(NAME)

# Bonus target, includes additional linked list functions
bonus: $(OBJS) $(BONUS_OBJS)
	@echo "$(LIGHT_BLUE)Adding bonus files to $(NAME)...$(RESET)"
	$(LIBC) $(NAME) $(OBJS) $(BONUS_OBJS)

so:
	@echo "$(LIGHT_BLUE)Creating shared library libft.so...$(RESET)"
	$(CC) -nostartfiles -fPIC ${CFLAGS} ${SRCS}
	$(CC) -nostartfiles -shared -o libft.so ${OBJS} $(BONUS_OBJS)

clean:
	@echo "$(LIGHT_BLUE)Cleaning up object files...$(RESET)"
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@echo "$(LIGHT_BLUE)Removing $(NAME) and libft.so...$(RESET)"
	$(RM) $(NAME)
	$(RM) libft.so

re: fclean all

.PHONY: all bonus so clean fclean re
	   
