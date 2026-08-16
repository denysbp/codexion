NAME := codexion
FLAGS := -Wall -Wextra -Werror -pthread
CC := cc
FOLDER := src


SRC := \
	$(FOLDER)/main.c \
	$(FOLDER)/parser.c \
	$(FOLDER)/parser_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -Iincludes -o $(NAME)

no-flags: $(OBJ)
	$(CC) $(OBJ) -Iincludes -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean all re OBJ NAME