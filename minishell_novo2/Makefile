# Compiler
CC = cc
CFLAGS := -g -Wall -Wextra -Werror -Iincludes

# Directories
SRCDIR = srcs
OBJDIR = objs

# Source files
SRCFILES = $(shell find $(SRCDIR) -type f -name "*.c")
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

# Executable name
NAME = minishell

# Rules
all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME) -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Memory leak check with valgrind
memcheck: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-trace=yes ./$(NAME)

.PHONY: all clean fclean re memcheck

.SILENT: