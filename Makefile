NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
CC = gcc
OBJ = printf.o file1.o file2.o file3.o file4.o file5.o file6.o file7.o

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
