# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 10:50:26 by jnovack           #+#    #+#              #
#    Updated: 2025/02/27 14:13:18 by jnovack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===================================
#|         COMPILATION            |#
#===================================
CC = gcc
CFLAGS = -Wall -Werror -Wextra

#===================================
#|          COMMANDS              |#
#===================================
RM = rm -rf

#===================================
#|         DIRECTORIES            |#
#===================================
LIBFTDIR = libft/
LIBFTLIB = libft/libft.a
SRC_DIR = sources/
OBJDIR = objs/

#===================================
#|         FILES                  |#
#===================================
SRC_FILES = main.c \
		sort_radix.c \
		stack_bits.c \
		stack_nodes.c \
		stack_init.c \
		op_push.c \
		op_rotate.c \
		op_revrotate.c \
		op_swap.c \
		val_utils.c \
		general_utils.c \
		stack_normalize.c \
		sort_small.c \
		sort_stack.c \
		sort_five.c
		

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJDIR), $(SRC_FILES:.c=.o))
NAME = push_swap

#===================================
#|         RULES                  |#
#===================================
all: $(LIBFTLIB) $(NAME)
	@echo "                                                                                                    "
	@echo "\033[32m#####  ██████╗ ██╗   ██╗███████╗██╗  ██╗    ███████╗██╗    ██╗ █████╗ ██████╗   #####\033[0m"
	@echo "\033[32m#####  ██╔══██╗██║   ██║██╔════╝██║  ██║    ██╔════╝██║    ██║██╔══██╗██╔══██╗  #####\033[0m"
	@echo "\033[32m#####  ██████╔╝██║   ██║███████╗███████║    ███████╗██║ █╗ ██║███████║██████╔╝  #####\033[0m"
	@echo "\033[32m#####  ██╔═══╝ ██║   ██║╚════██║██╔══██║    ╚════██║██║███╗██║██╔══██║██╔═══╝   #####\033[0m"
	@echo "\033[32m#####  ██║     ╚██████╔╝███████║██║  ██║    ███████║╚███╔███╔╝██║  ██║██║       #####\033[0m"
	@echo "\033[32m#####  ╚═╝      ╚═════╝ ╚══════╝╚═╝  ╚═╝    ╚══╝╚══╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝╚═╝       #####\033[0m"
	@echo "\033[32m The Makefile of [PUSH_SWAP] has been compiled!\033[0m"

$(OBJDIR):
	@mkdir -p $@

$(NAME): $(OBJ) $(LIBFTLIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTLIB) -o $(NAME)

$(OBJDIR)%.o: $(SRC_DIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFTLIB):
	@make -C $(LIBFTDIR) --no-print-directory

clean:
	$(RM) $(OBJDIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re

