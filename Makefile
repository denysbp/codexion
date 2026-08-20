NAME := codexion
FLAGS := -Wall -Wextra -Werror -pthread
CC := cc
FOLDER := src
ENGINE := $(FOLDER)/engine
CODER := $(FOLDER)/coder
HEAP := $(FOLDER)/heap
PARSER := $(FOLDER)/parser


SRC := \
	$(FOLDER)/main.c \
	$(PARSER)/parser.c \
	$(PARSER)/parser_utils.c \
	$(CODER)/coder.c \
	$(CODER)/routine.c \
	$(CODER)/simulation.c \
	$(CODER)/helps.c \
	$(HEAP)/heap.c \
	$(HEAP)/helps.c \
	$(ENGINE)/engine.c \
	$(ENGINE)/scheduler.c \
	$(ENGINE)/monitoring.c \
	$(FOLDER)/helps.c \

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