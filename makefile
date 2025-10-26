# Makefile

NAME = sokoban

SRCS = main.c \
	fonction.c \
	print_tab.c \
	str_cpy.c \
	str_len.c 


all: $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all