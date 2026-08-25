NAME := codexion
FLAGS := -Wall -Wextra -Werror -pthread
CC := cc
FOLDER := src
ENGINE := $(FOLDER)/engine
CODER := $(FOLDER)/coder
HEAP := $(FOLDER)/heap
PARSER := $(FOLDER)/parser
TRASH := trash/


SRC := \
	$(FOLDER)/main.c \
	$(PARSER)/parser.c \
	$(PARSER)/parser_utils.c \
	$(CODER)/coder.c \
	$(CODER)/routine.c \
	$(CODER)/simulation.c \
	$(CODER)/helps.c \
	$(CODER)/helps_utils.c \
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

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@found=0; \
	for obj in $(OBJ); do \
		if [ -f "$$obj" ]; then \
			rm -f "$$obj"; \
			printf "rm -rf %s\n" "$$obj"; \
			found=1; \
		fi; \
	done; \
	if [ $$found -eq 0 ]; then \
		echo "Nothing to do with make 'clean'"; \
	fi

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: fclean all re clean