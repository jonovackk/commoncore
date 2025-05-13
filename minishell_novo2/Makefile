# Compiler
CC = cc
CFLAGS := -g -Wall -Wextra -Werror -Iincludes -Ilibft

# Directories
SRCDIR = srcs
OBJDIR = objs
LIBFTDIR = libft

# Source files
SRCFILES = $(shell find $(SRCDIR) -type f -name "*.c")
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

# Executable name
NAME = minishell

# Libft library
LIBFT = $(LIBFTDIR)/libft.a

# Rules
all: $(NAME)

$(NAME): $(OBJFILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME) -L$(LIBFTDIR) -lft -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

# Memory leak check with valgrind
memcheck: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-trace=yes ./$(NAME)

.PHONY: all clean fclean re memcheck

