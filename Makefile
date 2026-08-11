NAME := codexion
FLAGS := -Wall -Wextra -Werror -pthread
CC := cc
FOLDER := src


SRC := \
	$(FOLDER)/main.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -Iincludes -o $(NAME)


%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean all re OBJ NAME